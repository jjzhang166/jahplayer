//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHIMAGESEQUENCE_H
#define JAHIMAGESEQUENCE_H

#include "JahIdMedia.h"
#include <QImage>
#include <QVector>

/**
 * @brief The JahImageSequence class
 *  define a list of playable images
 *  load and cache images in background
 */
class JahImageSequence : public QObject
{
    Q_OBJECT
public:

    JahImageSequence(QObject *parent = 0);

    /** get the first sequence image */
    QImage thumbnail();

    /** set current image index to 0 */
    void start();

    /** check if more images available */
    bool finished() const;

    /** get current image, increment */
    QImage next();

    /**
     * @brief setSequence
     *  assign a sequence of images as files
     * @param reference
     *  identifier as required by QMedia
     * @param name
     *  symbol exposed to user
     * @param folder
     *  common path to all filenames
     * @param images
     *  filenames, share folder
     */
    void setSequence(JahIdMedia reference, QStringList images);

    /**
     * @brief setCurrentFrame
     *  change current image (played next) as required
     * @param frame
     *  in range frame index
     */
    void setCurrentFrame(int frame);

    /** access protocol of QMediaObject */
    const JahIdMedia &getReference() const { return reference; }

    /** user visible name */
    QString getUserVisibleName() const { return name; }

    /** load test data, from test folders */
    void loadFromFolder(QString folder);

    /**
     * @brief currentPosition
     *  access index of next to play frame
     */
    qint64 currentPosition() const { return curr; }

    /**
     * @brief totFrames
     *  number of frames in full sequence
     */
    qint64 totFrames() const { return cache.size(); }

signals:

    /** cache content ready to play */
    void ready();

private:

    JahIdMedia reference;
    QString name;

    struct frame {
        QString name;
        QImage data;
        bool load(QString dir);
    };
    QVector<frame> cache;

    /** current image index */
    int curr = -1;
};

#endif // JAHIMAGESEQUENCE_H
