##
##  This file is part of Jahshaka
##  Copyright (c) 2016 Sputnik7 (MIT)
##
##  This is free software: you may copy, redistribute
##  and/or modify it under the terms of the MIT License
##

QT += core gui multimedia multimediawidgets widgets concurrent sql

TARGET = video_from_images
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    JahVideoSurface.cpp \
    JahVideoWidget.cpp \
    JahMediaPlayer.cpp \
    JahPlayerUIControls.cpp \
    JahThumbnails.cpp \
    JahSettings.cpp \
    JahDatabase.cpp \
    JahException.cpp \
    JahIdMedia.cpp \
    JahImageSequence.cpp \
    JahHistogramWidget.cpp

HEADERS += \
    mainwindow.h \
    JahVideoSurface.h \
    JahVideoWidget.h \
    JahMediaPlayer.h \
    JahPlayerUIControls.h \
    JahThumbnails.h \
    JahSettings.h \
    JahDatabase.h \
    JahException.h \
    JahImageSequence.h \
    JahIdMedia.h \
    JahHistogramWidget.h

CONFIG += mobility
MOBILITY =

RESOURCES += \
    jahplayer.qrc

DISTFILES += \
    resources/jahplayer-logo.jpg \
    resources/jahplayer-icon.png

