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

//! there are some difficulties building X264 on CentOS 7
#ifdef _JAH_USE_X264_ENCODER_
#include "JahEncoder.h"
#else
class JahEncoder {};
#endif

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

    void removeHistogram();
    void displayHistogram();

    void enableEncoding(QString output_file);
    void disableEncoding();

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
    JahThumbnails *getThumbnails() const { return thumbnails; }

    /** get actual frame player to change on user request */
    JahImageSequence* getSequence() const { return sequence; }

signals:
    void durationChanged(qint64);
    void positionChanged(qint64);

    void frameAvailable(QVideoFrame frame);

public slots:

protected slots:
    void onTimer();

protected:

    virtual void paintEvent(QPaintEvent *event);

    virtual bool setMediaObject(QMediaObject *object);

    JahImageSequence* sequence = 0;
    JahThumbnails* thumbnails = 0;

    //! there are some difficulties building X264 on CentOS 7
    JahEncoder* encoder = 0;

    QTimer timer;
    QImage last_drawn;
};

#endif // JAHVIDEOWIDGET_H
