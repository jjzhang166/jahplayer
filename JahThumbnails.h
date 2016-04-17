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

    JahDatabase *database;
    JahImageSequence* current();

    JahImageSequence* fromUrl(QUrl url);

signals:

    void selected(QUrl resource);

public slots:

private:

    void initFromFolder();
    void initFromDb();

    QVector<JahImageSequence*> sequences;
};

#endif // JAHTHUMBNAILS_H
