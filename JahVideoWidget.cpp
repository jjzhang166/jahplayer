//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahVideoWidget.h"
#include <QPaintEngine>
#include <QDebug>

JahVideoWidget::JahVideoWidget(QWidget *parent) : QWidget(parent) {

}

bool JahVideoWidget::present(const QVideoFrame &frame) {
    qDebug() << "present" << frame;
    return false;
}

QList<QVideoFrame::PixelFormat> JahVideoWidget::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const {
    qDebug() << "supportedPixelFormats" << type;
    return QList<QVideoFrame::PixelFormat>();
}

QMediaObject *JahVideoWidget::mediaObject() const {
    qDebug() << "mediaObject";
    return 0;
}

bool JahVideoWidget::setMediaObject(QMediaObject *object) {
    qDebug() << "setMediaObject" << object;
    return false;
}

void JahVideoWidget::play() {
    timer.start(100);
    connect(&timer, &QTimer::timeout, this, &JahVideoWidget::onTimer);
}
void JahVideoWidget::onTimer() {
    if (sequence) {
        if (sequence->finished())
            timer.stop();
        else
            update();
    }
}
void JahVideoWidget::paintEvent(QPaintEvent *event) {
    auto drawImage = [this, event](QImage i) {
        QPainter p(this);
        p.drawImage(event->rect(), i, i.rect());
    };

    if (sequence && timer.isActive()) {
        auto i = sequence->next();
        if (!i.isNull()) {
            emit positionChanged(sequence->currentPosition());
            qDebug() << "emit positionChanged(sequence->currentPosition());";

            drawImage(last_drawn = i);
            return;
        }
    }
    if (!last_drawn.isNull())
        drawImage(last_drawn);
}

void JahVideoWidget::stop() {
    timer.stop();
}
void JahVideoWidget::pause() {
    timer.stop();
}

void JahVideoWidget::setMedia(QUrl url) {
    /*
    auto s = url.toString();
    if (s.left(7) == "file://")
        s = s.mid(7);
    else if (s.left(5) == "file:")
        s = s.mid(5);
    else
        return;

    delete sequence;
    sequence = new JahImageSequence();
    //sequence->setFolder(s);
    sequence->start();
    */
    sequence = thumbnails->fromUrl(url);
    sequence->start();

    emit durationChanged(timer.interval() * sequence->totFrames());
}

void JahVideoWidget::setFPS(int fps) {
    timer.stop();
    timer.start(1000 / fps);

    emit durationChanged(timer.interval() * sequence->totFrames());
}
