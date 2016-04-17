//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahMediaPlayer.h"
#include <QDebug>

JahMediaPlayer::JahMediaPlayer(QObject *parent) : QMediaPlayer(parent) {

}

/* TBD void JahMediaPlayer::setVideoOutput(QAbstractVideoSurface *) {
}*/
void JahMediaPlayer::setVideoOutput(JahVideoWidget *widget) {
    videoWidget = widget;
    connect(videoWidget, SIGNAL(durationChanged(qint64)), this, SIGNAL(durationChanged(qint64)));
    connect(videoWidget, SIGNAL(positionChanged(qint64)), this, SIGNAL(positionChanged(qint64)));
}

void JahMediaPlayer::setMedia(QUrl url) {
    mediaUrl = url;
    if (videoWidget)
        videoWidget->setMedia(url);
}

void JahMediaPlayer::play() {
    if (videoWidget)
        videoWidget->play();
}

void JahMediaPlayer::stop() {
    if (videoWidget)
        videoWidget->stop();
}

void JahMediaPlayer::pause() {
    if (videoWidget)
        videoWidget->pause();
}
/*
connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
        this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
*/
