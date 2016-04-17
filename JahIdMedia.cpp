//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahIdMedia.h"
#include <QUrlQuery>
#include <QDebug>

JahIdMedia::JahIdMedia() {
    defineUrl();
}

JahIdMedia::JahIdMedia(const JahIdMedia &other) : QUrl(other) {
    defineUrl(other.path(), other.name(), other.media(), other.frameStart(), other.frameEnd());
}

JahIdMedia::JahIdMedia(QString name, QString folder, int media, int frameStart, int frameEnd) {
    defineUrl(folder, name, media, frameStart, frameEnd);
}

void JahIdMedia::defineUrl(QString path, QString name, int media, int frameStart, int frameEnd) {
    setScheme(jah_scheme());
    setHost(jah_host());
    //setPath("/DB");

    QUrlQuery q;
    q.addQueryItem("path", path);
    q.addQueryItem("name", name);
    q.addQueryItem("media", QString::number(media));
    q.addQueryItem("frameStart", QString::number(frameStart));
    q.addQueryItem("frameEnd", QString::number(frameEnd));
    setQuery(q.query());
}

QString JahIdMedia::imagePath() const {
    return path() + '/' + name();
}

QString JahIdMedia::path() const {
    QUrlQuery q(*this);
    return q.hasQueryItem("path") ? q.queryItemValue("path") : QString();
}
QString JahIdMedia::name() const {
    QUrlQuery q(*this);
    return q.hasQueryItem("name") ? q.queryItemValue("name") : QString();
}
int JahIdMedia::media() const {
    QUrlQuery q(*this);
    return q.hasQueryItem("media") ? q.queryItemValue("media").toInt() : -1;
}
int JahIdMedia::frameStart() const {
    QUrlQuery q(*this);
    return q.hasQueryItem("frameStart") ? q.queryItemValue("frameStart").toInt() : -1;
}
int JahIdMedia::frameEnd() const {
    QUrlQuery q(*this);
    return q.hasQueryItem("frameEnd") ? q.queryItemValue("frameEnd").toInt() : -1;
}

QString JahIdMedia::namePatternFromNumeric(QString fileNumber, QString fileNonum) {
    return fileNonum + '_' + QString(fileNumber.length() - fileNonum.length() - 1, QChar('$'));
}

QString JahIdMedia::namePatternAssignNumber(QString filePattern, int number, QString fileExt) {
    int p = filePattern.indexOf('$');
    Q_ASSERT(p > 0);
    return QString("%1%2.%3").arg(filePattern.left(p)).arg(number, filePattern.length() - p, 10, QChar('0')).arg(fileExt);
}
