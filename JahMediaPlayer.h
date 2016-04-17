//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHMEDIAPLAYER_H
#define JAHMEDIAPLAYER_H

#include <QPointer>
#include <QMediaPlayer>
#include <QUrl>

//#include <QAbstractVideoSurface>
#include "JahVideoWidget.h"

/**
 * @brief The JahMediaPlayer class
 *  attempt a QMedia framework compatibility layer
 */
class JahMediaPlayer : public QMediaPlayer
{
    Q_OBJECT

    QPointer<JahVideoWidget> videoWidget;
    QUrl mediaUrl;

public:

    explicit JahMediaPlayer(QObject *parent = 0);

    /**
     * @brief setMedia
     *  define what to play
     * @param url
     *  check if @arg url is a JahIdMedia,
     *  then forward it to videoWidget
     */
    void setMedia(QUrl url);

    //void setVideoOutput(QAbstractVideoSurface *);
    void setVideoOutput(JahVideoWidget* widget);
    JahVideoWidget* videoOutput() const { return videoWidget; }

signals:
    void durationChanged(qint64);
    void positionChanged(qint64);

public slots:

    void pause();
    void play();
    void stop();

};

#endif // JAHMEDIAPLAYER_H
