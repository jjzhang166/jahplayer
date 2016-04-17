//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHDATABASE_H
#define JAHDATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include "JahIdMedia.h"
#include "JahSettings.h"
#include "JahIdMedia.h"

/**
 * @brief The JahDatabase class
 *  handle persistent media (images sequences) definitions
 */
class JahDatabase : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief JahDatabase
     *  handle initialization, file path defined in JahSettings
     * @param parent
     *  standard Qt object model
     */
    JahDatabase(QObject *parent = 0);

    /**
     * @brief The definition struct
     *  what is needed to play a definition using QMedia framework
     */
    struct definition {
        JahIdMedia id;
        QStringList files;
    };

    /**
     * @brief definitions
     *  load all media definitions (images sequences)
     * @return
     *  named images sequences
     */
    QList<definition> allDefinitions();

    /**
     * @brief all_references
     * @return
     *  all DB defined media identifiers
     */
    QList<JahIdMedia> allReferences();

    /**
     * @brief get_definition
     *  fetch resource definition from DB
     * @param id
     *  media resource idetifier
     * @return
     *  sought definition, or throw
     */
    definition getDefinition(const JahIdMedia &id);

private:

    /** physical storage, file path defined in JahSettings */
    QSqlDatabase database;

    void createNew();
    void checkStructure(const JahSettings &settings);
    void addTestImages(const JahSettings &settings);
};

#endif // JAHDATABASE_H
