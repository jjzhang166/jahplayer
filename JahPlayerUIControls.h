//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHPLAYERUICONTROLS_H
#define JAHPLAYERUICONTROLS_H

#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QAbstractButton>

#include "JahMediaPlayer.h"

/**
 * @brief The JahPlayerUIControls class
 *  define a set of UI options and commands to run a JahPlayer media presentation
 */
class JahPlayerUIControls : public QWidget
{
    Q_OBJECT

public:

    explicit JahPlayerUIControls(QWidget *parent = 0);

    void routeBehaviour(JahMediaPlayer *mediaPlayer);

signals:

public slots:

private:

    QAbstractButton
        *Play = 0,
        *Stop = 0,
        *Pause = 0,
        *SkipForward = 0,
        *SkipBackward = 0,
        *SeekForward = 0,
        *SeekBackward = 0,
        *Volume = 0,
        *VolumeMuted = 0;

    QLabel
        *frameCount = 0,
        *timeOffset = 0;
    QSlider
        *slider = 0;

    QComboBox
        *fpsBox = 0;

    //! could be static by now
    int fpsCurrent(int comboIndex) const;
};

#endif // JAHPLAYERUICONTROLS_H
