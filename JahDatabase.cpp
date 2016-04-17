//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahDatabase.h"
#include "JahException.h"

#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QElapsedTimer>
#include <QRegularExpression>

#define T0 "desktop"
#define T1 "videodata"

JahDatabase::JahDatabase(QObject *parent) : QObject(parent) {
    JahSettings settings;
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString db_name = settings.sqlitePath + '/' + settings.sqliteName;
    database.setDatabaseName(db_name);
    if (!database.open())
        throw JahException(tr("cannot open database '%1'").arg(db_name));
    checkStructure(settings);
}

QList<JahDatabase::definition> JahDatabase::allDefinitions() {
    QList<JahDatabase::definition> l;
    for (auto r : allReferences())
        l << getDefinition(r);
    return l;
}

QList<JahIdMedia> JahDatabase::allReferences() {
    QList<JahIdMedia> l;
    for (QSqlQuery q("SELECT DISTINCT MediaName,FileLocation,MediaNumber,StartFrame,EndFrame FROM " T1); q.next(); )
        l << JahIdMedia(q.value(0).toString(), q.value(1).toString(), q.value(2).toInt(), q.value(3).toInt(), q.value(4).toInt());
    return l;
}

JahDatabase::definition JahDatabase::getDefinition(const JahIdMedia& id) {
    qDebug() << id.toString();

    definition d { id, {} };

    auto s = QString("SELECT FileName,StartFrame,EndFrame,FileExtension FROM " T1
                     " WHERE MediaName='%1' AND MediaNumber=%2").arg(id.name()).arg(id.media());
                     // " WHERE MediaName='%1' AND FileLocation='%2'").arg(id.name(), id.path());
    for (QSqlQuery q(s); q.next(); ) {
        auto FileName = q.value(0).toString();
        auto FileExt = q.value(3).toString();
        int StartFrame = q.value(1).toInt();
        int EndFrame = q.value(2).toInt();
        for (int p = StartFrame; p <= EndFrame; ++p)
            d.files << JahIdMedia::namePatternAssignNumber(FileName, p, FileExt);
    }
    return d;
}
/*
void JahDatabase::addTestImages(const JahSettings &settings) {

    QSqlQuery query(database);

    query.exec("PRAGMA synchronous = OFF");
    query.exec("PRAGMA journal_mode = MEMORY");
    query.exec("BEGIN TRANSACTION");

    QString Category = "test";
    QString Cliptype = "reel";
    QString Videoext = "MOV";
    QString MediaName;
    int MediaNumber = 0;
    QString FileLocation;
    QString FileName;
    QString FileExtension = "image";
    int StartFrame;
    int EndFrame;
    int xpos = 0;
    int ypos = 0;
    query.prepare("INSERT INTO " T1 "("
        "Category,Cliptype,Videoext,MediaName,MediaNumber,"
        "FileLocation,FileName,FileExtension,"
        "StartFrame,EndFrame,xpos,ypos"
        ") VALUES (?,?,?,?,?,?,?,?,?,?,?,?)"
    );

    QElapsedTimer timer;
    timer.start();
    int count = 0;

    auto base = settings.folderImages;
    QDir dir(base);
    for (auto folder: dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name)) {
        FileLocation = base + '/' + folder;
        QDir dir(FileLocation);
        MediaNumber++;
        MediaName = folder;
        StartFrame = EndFrame = 0;
        for (auto name : dir.entryList({"*.jpg", "*.BMP"}, QDir::Files, QDir::Name)) {
            FileName = name;
            query.bindValue(0, Category);
            query.bindValue(1, Cliptype);
            query.bindValue(2, Videoext);
            query.bindValue(3, MediaName);
            query.bindValue(4, MediaNumber);
            query.bindValue(5, FileLocation);
            query.bindValue(6, FileName);
            query.bindValue(7, FileExtension);
            query.bindValue(8, StartFrame);
            query.bindValue(9, EndFrame);
            ++EndFrame;
            query.bindValue(10, xpos);
            query.bindValue(11, ypos);
            if (!query.exec())
                throw JahException(tr("cannot insert record %1 in table " T1).arg(count));
            ++count;
        }
    }
    query.exec("END TRANSACTION");

    qDebug() << "inserted " << count << " in " << timer.elapsed();
}
*/
void JahDatabase::addTestImages(const JahSettings &settings) {

    QSqlQuery query(database);

    query.exec("PRAGMA synchronous = OFF");
    query.exec("PRAGMA journal_mode = MEMORY");
    query.exec("BEGIN TRANSACTION");

    QString Category = "test";
    QString Cliptype = "reel";
    QString Videoext = "MOV";
    QString MediaName;
    int MediaNumber = 0;
    QString FileLocation;
    QString FileName;
    QString FileExtension;
    int StartFrame;
    int EndFrame;
    int xpos = 0;
    int ypos = 0;
    query.prepare("INSERT INTO " T1 "("
        "Category,Cliptype,Videoext,MediaName,MediaNumber,"
        "FileLocation,FileName,FileExtension,"
        "StartFrame,EndFrame,xpos,ypos"
        ") VALUES (?,?,?,?,?,?,?,?,?,?,?,?)"
    );

    QElapsedTimer timer;
    timer.start();
    int count = 0;

    auto base = settings.folderImages;
    QDir dir(base);
    for (auto folder: dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name)) {
        FileLocation = base + '/' + folder;

        QDir dir(FileLocation);
        MediaNumber++;

        MediaName = folder;

        //! scan sorted entries for sequentially numbered images
        StartFrame = EndFrame = -1;
        FileName = FileExtension = "";
        QString file_nonum, file_number;

        QRegularExpression re("([\\w\\d_]+)_(\\d+)\\.(\\w+)");
        for (auto name : dir.entryList(QDir::Files, QDir::Name)) {
            auto mt = re.match(name);
            if (mt.hasMatch()) {
                auto l = mt.capturedTexts();
                if (StartFrame == -1) {
                    file_nonum = l[1];
                    StartFrame = l[2].toInt();
                    FileExtension = l[3];
                    file_number = name.mid(0, mt.capturedStart(3) - 1);
                }
                else if (file_nonum == l[1] && FileExtension == l[3])
                    EndFrame = l[2].toInt();
                else
                    qDebug() << "mismatch" << name << "with" << file_nonum << FileExtension;
            }
        }
        if (EndFrame > StartFrame) {
            //! replace numerics (like 0023) with $$$$
            FileName = JahIdMedia::namePatternFromNumeric(file_number, file_nonum);
            query.bindValue(0, Category);
            query.bindValue(1, Cliptype);
            query.bindValue(2, Videoext);
            query.bindValue(3, MediaName);
            query.bindValue(4, MediaNumber);
            query.bindValue(5, FileLocation);
            query.bindValue(6, FileName);
            query.bindValue(7, FileExtension);
            query.bindValue(8, StartFrame);
            query.bindValue(9, EndFrame);

            query.bindValue(10, xpos);  // ??
            query.bindValue(11, ypos);
            if (!query.exec())
                throw JahException(tr("cannot insert record %1 in table " T1).arg(count));
            ++count;
        }
    }
    query.exec("END TRANSACTION");

    qDebug() << "inserted " << count << " in " << timer.elapsed();
}

void JahDatabase::checkStructure(const JahSettings &settings) {
    QSqlQuery q("SELECT name FROM sqlite_master WHERE type='table'", database);
    QStringList tables;
    while (q.next())
        tables << q.value(0).toString();
    if (!tables.contains(T0) || !tables.contains(T1)) {
        createNew();
        addTestImages(settings);
    }
}

void JahDatabase::createNew() {
    QSqlQuery q(database);
    if (!q.exec("CREATE TABLE " T0 "(name VARCHAR(55), numclips INT)"))
        throw JahException(tr("cannot create table %1").arg(T0));
    if (!q.exec("CREATE TABLE " T1 "(Category VARCHAR(12), Cliptype VARCHAR(12), Videoext VARCHAR(9), MediaName VARCHAR(128), MediaNumber INT, FileLocation VARCHAR(255), FileName VARCHAR(255), FileExtension VARCHAR(12), StartFrame INT, EndFrame INT, xpos INT, ypos INT)"))
        throw JahException(tr("cannot create table %1").arg(T1));
    if (!q.exec("CREATE INDEX DesktopID ON " T1 " (MediaName)"))
        throw JahException(tr("cannot create INDEX %1").arg("DesktopID"));
    if (!q.exec("INSERT INTO " T0 " VALUES('desktop', 0)") || !q.isActive())
        throw JahException(tr("cannot insert '%1' in table " T0).arg("0"));
}
