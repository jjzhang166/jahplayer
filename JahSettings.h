//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHSETTINGS_H
#define JAHSETTINGS_H

#include <QSettings>
#include <QWidget>

/**
 * @brief The JahSettings class
 *  handle UI settings storage
 */
class JahSettings : public QSettings
{
    Q_OBJECT
public:

    /** load current settings */
    JahSettings(QObject *parent = 0);

    /** where to look for images sequences */
    QString folderImages;

    /** where to look for SQLITE definition database */
    QString sqlitePath;

    /** name of global definitions SQLITE DB */
    QString sqliteName;

    /** helpers to save/restore windows placements */
    void loadGeometry(QWidget *w);
    void saveGeometry(QWidget *w);

    void loadGeometry(QString key, QWidget *w);
    void saveGeometry(QString key, QWidget *w);

    void loadPosSizeState(QString key, QWidget *w);
    void savePosSizeState(QString key, QWidget *w);
};

#endif // JAHSETTINGS_H
