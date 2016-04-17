//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHVIDEOWIDGET_H
#define JAHVIDEOWIDGET_H

#include <QUrl>
#include <QTimer>
#include <QWidget>
#include <QPaintEvent>
#include <QAbstractVideoSurface>
#include <QMediaBindableInterface>

#include "JahThumbnails.h"

class JahVideoWidget : public QWidget, public QMediaBindableInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaBindableInterface)

public:
    explicit JahVideoWidget(QWidget *parent = 0);

    virtual bool present(const QVideoFrame &frame);
    virtual QList<QVideoFrame::PixelFormat>
        supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;

    virtual QMediaObject *mediaObject() const;

    /// workaround while learning about proper interfacing QMedia
    void play();
    void stop();
    void pause();
    void setMedia(QUrl url);

    /**
     * @brief setFPS
     *  adjust running time, emits durationChanged
     * @param fps
     *  frames per second
     */
    void setFPS(int fps);

    /**
     * @brief setThumbnails
     *  assign DB loader
     * @param t
     *  DB loader
     */
    void setThumbnails(JahThumbnails *t) { thumbnails = t; }
    JahThumbnails *thumbnails_() const { return thumbnails; }

signals:
    void durationChanged(qint64);
    void positionChanged(qint64);

public slots:

protected slots:
    void onTimer();

protected:

    virtual void paintEvent(QPaintEvent *event);

    virtual bool setMediaObject(QMediaObject *object);

    JahImageSequence* sequence = 0;
    JahThumbnails* thumbnails = 0;

    QTimer timer;
    QImage last_drawn;
};

#endif // JAHVIDEOWIDGET_H
