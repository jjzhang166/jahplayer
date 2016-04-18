//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahPlayerUIControls.h"
#include "JahVideoWidget.h"
#include "JahException.h"

#include <QTime>
#include <QStyle>
#include <QToolButton>
#include <QHBoxLayout>

inline QString zeroPad(int i, int zeros = 6) {
    return QString("%1").arg(i, zeros, 10, QChar('0'));
}
inline QString pairs(QString l, QString r, QChar sep = '/') {
    return l + sep + r;
}
inline QString times(qint64 msec) {
    return QTime(QTime(0, 0).addMSecs(msec)).toString("hh:mm:ss.zzz");
}

JahPlayerUIControls::JahPlayerUIControls(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *v = new QVBoxLayout;
    QBoxLayout *h = new QHBoxLayout;
    QBoxLayout *s = new QHBoxLayout;

    #define CMD(c) { \
        auto b = new QToolButton(this); \
        b->setIcon(style()->standardIcon(QStyle::SP_Media##c)); \
        b->setToolTip(#c); \
        b->setAutoRaise(true); \
        h->addWidget(c = b); \
    }

    CMD(Play)
    CMD(Stop)
    CMD(Pause)
    CMD(SkipForward)
    CMD(SkipBackward)
    CMD(SeekForward)
    CMD(SeekBackward)
    CMD(Volume)
    CMD(VolumeMuted)
    v->addLayout(h);

    s->addWidget(frameCount = new QLabel(pairs(zeroPad(0), zeroPad(0))));
    frameCount->setToolTip(tr("frames count"));

    s->addWidget(slider = new QSlider(Qt::Horizontal));
    slider->setToolTip(tr("current frame offset"));

    auto to = times(0);
    s->addWidget(timeOffset = new QLabel(pairs(to, to)));
    timeOffset->setToolTip(tr("current time offset"));

    s->addWidget(fpsBox = new QComboBox);
    for (int v: {1, 10, 30, 60})
        fpsBox->addItem(QString("%1 fps").arg(v), QVariant(v));

    v->addLayout(s);
    setLayout(v);
}

int JahPlayerUIControls::fpsCurrent(int index) const {
    if (index == -1)
        index = fpsBox->currentIndex();
    if (index >= 0)
        return fpsBox->itemData(index).toInt();
    throw JahException(tr("internal error"));
}

void JahPlayerUIControls::routeBehaviour(JahMediaPlayer *p) {

    connect(Play, &QAbstractButton::clicked, [this, p]() {
        auto v = p->videoOutput();
        auto l = v->getThumbnails();
        if (auto i = l->current()) {
            i->start();
            p->setMedia(i->getReference());
            p->play();
            v->setFPS(fpsCurrent(-1));
            slider->setRange(0, i->totFrames());
        }
    });
    connect(Stop, &QAbstractButton::clicked, [p]() {
        p->stop();
    });
    connect(Pause, &QAbstractButton::clicked, [p]() {
        p->pause();
    });

    connect(p, &QMediaPlayer::durationChanged, [](qint64 dur) {
        qDebug() << "durationChanged" << dur;
    });

    //connect(p, &QMediaPlayer::positionChanged, [this](qint64 pos) {
    //connect(p->videoOutput(), &JahVideoWidget::positionChanged, [this](qint64 pos) {
    connect(p, &JahMediaPlayer::positionChanged, [this](qint64 pos) {
        slider->setValue(pos);
        int durFrame = 1000 / fpsCurrent(-1);
        timeOffset->setText(pairs(times(pos * durFrame), times(slider->maximum() * durFrame)));
        frameCount->setText(pairs(zeroPad(pos), zeroPad(slider->maximum())));
    });

    connect(slider, &QSlider::sliderReleased, [p, this]() {
        p->videoOutput()->getSequence()->setCurrentFrame(slider->value());
    });

    /*
    connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
    */

    connect(fpsBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, p](int index) {
        p->videoOutput()->setFPS(fpsCurrent(index));
    });
}
