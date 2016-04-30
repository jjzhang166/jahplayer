//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahVideoWidget.h"
#include "JahHistogramWidget.h"
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

template <class T>
inline T *findChildByClass(QWidget *parent) {
    for (auto c : parent->children())
        if (auto w = qobject_cast<T*>(c))
            return w;
    return nullptr;
}

void JahVideoWidget::removeHistogram() {
    auto histo = findChildByClass<JahHistogramWidget>(this);
    Q_ASSERT(histo);
    delete histo;
}

void JahVideoWidget::displayHistogram() {
    Q_ASSERT(!findChildByClass<JahHistogramWidget>(this));
    auto histo = new JahHistogramWidget(this);
    auto h = height(), w = width();
    histo->resize(w, h / 8);
    histo->move(0, h - h / 8);
    histo->show();
    connect(this, &JahVideoWidget::frameAvailable, histo, &JahHistogramWidget::processFrame);
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
            drawImage(last_drawn = i);
            emit frameAvailable(last_drawn);
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
    sequence = thumbnails->fromUrl(url);
    sequence->start();
    emit durationChanged(timer.interval() * sequence->totFrames());
}

void JahVideoWidget::setFPS(int fps) {
    timer.stop();
    timer.start(1000 / fps);
    emit durationChanged(timer.interval() * sequence->totFrames());
}

void JahVideoWidget::enableEncoding(QString output_file) {
    if (!encoder) {
        encoder = new JahEncoder;
        if (encoder->open(output_file))
            connect(this, &JahVideoWidget::frameAvailable, encoder, &JahEncoder::encode);
    }
}

void JahVideoWidget::disableEncoding() {
    delete encoder;
    encoder = 0;
}
