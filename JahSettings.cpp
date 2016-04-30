//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahSettings.h"
#include <QDir>

JahSettings::JahSettings(QObject *parent) :
    QSettings("Sputnik7", "JahPlayer", parent)
{
    folderImages = value("folderImages", "../jahplayer/resources/images/clips").toString();

    sqlitePath = value("sqlitePath", "../jahplayer/resources").toString();
    sqliteName = value("sqliteName", "jahplayer").toString();
    openDbHistory = value("openDbHistory", QStringList()).toStringList();
}

void JahSettings::save() {
    setValue("folderImages", folderImages);
    setValue("sqlitePath", sqlitePath);
    setValue("sqliteName", sqliteName);
    setValue("openDbHistory", openDbHistory);
}

void JahSettings::loadGeometry(QString key, QWidget *w) {
    w->restoreGeometry(value(key + "/geometry").toByteArray());
}
void JahSettings::saveGeometry(QString key, QWidget *w) {
    setValue(key + "/geometry", w->saveGeometry());
}
void JahSettings::loadGeometry(QWidget *w) {
    loadGeometry(w->metaObject()->className(), w);
}
void JahSettings::saveGeometry(QWidget *w) {
    saveGeometry(w->metaObject()->className(), w);
}

void JahSettings::loadPosSizeState(QString key, QWidget *w) {
    beginGroup(key);
    QPoint pos = value("pos", QPoint(40, 30)).toPoint();
    QSize size = value("size", QSize(400, 300)).toSize();
    int state = value("state", static_cast<int>(Qt::WindowNoState)).toInt();
    w->move(pos);
    w->resize(size);
    w->setWindowState(static_cast<Qt::WindowStates>(state));
    endGroup();
}

void JahSettings::savePosSizeState(QString key, QWidget *w) {
    beginGroup(key);
    setValue("pos", w->pos());
    setValue("size", w->size());
    setValue("state", static_cast<int>(w->windowState()));
    endGroup();
}
