//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHTHUMBNAILS_H
#define JAHTHUMBNAILS_H

#include <QUrl>
#include <QVector>
#include <QListWidget>

#include "JahDatabase.h"
#include "JahImageSequence.h"

/**
 * @brief The JahThumbnails class
 *  implements a DB view
 */
class JahThumbnails : public QListWidget
{
    Q_OBJECT

public:

    explicit JahThumbnails(QWidget *parent = 0);

    JahImageSequence* current();

    JahImageSequence* fromUrl(QUrl url);

    /**
     * @brief db
     *  the only media definition source
     * @return
     *  the current database
     */
    JahDatabase *db() const { return database; }

    /**
     * @brief connectToDb
     *  get DB path from settings and open it
     * @return
     *  true if DB opened and assets found
     */
    bool connectToDb();

    /**
     * @brief addAssetDirToDb
     *  store the sequence of images (only symbolic names) in DB
     * @param folder
     *  path of folder containing a correctly named images sequence
     * @return
     *  true if sequence added (folder name should be unique)
     */
    bool addAssetDirToDb(QString folder);

signals:

    void selected(QUrl resource);

public slots:

private:

    JahDatabase *database = 0;

    void initFromFolder();
    void initFromDb();

    QVector<JahImageSequence*> sequences;
};

#endif // JAHTHUMBNAILS_H
