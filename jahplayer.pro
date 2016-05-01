##
##  This file is part of Jahshaka
##  Copyright (c) 2016 Sputnik7 (MIT)
##
##  This is free software: you may copy, redistribute
##  and/or modify it under the terms of the MIT License
##

QT += core gui multimedia multimediawidgets widgets concurrent sql

TARGET = jahplayer
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

# there are some difficulties building X264 on CentOS 7
defined(_JAH_USE_X264_ENCODER_) {
    SOURCES += JahEncoder.cpp
    HEADERS += JahEncoder.h
    LIBS += -lavcodec -lswscale -lx264
}

CONFIG += mobility
MOBILITY =

RESOURCES += \
    jahplayer.qrc

DISTFILES += \
    resources/jahplayer-logo.jpg \
    resources/jahplayer-icon.png \
    resources/images/clips/explosion/explosion_00036.jpg \
    resources/images/clips/explosion/explosion_00035.jpg \
    resources/images/clips/explosion/explosion_00034.jpg \
    resources/images/clips/explosion/explosion_00033.jpg \
    resources/images/clips/explosion/explosion_00032.jpg \
    resources/images/clips/explosion/explosion_00031.jpg \
    resources/images/clips/explosion/explosion_00030.jpg \
    resources/images/clips/explosion/explosion_00029.jpg \
    resources/images/clips/explosion/explosion_00028.jpg \
    resources/images/clips/explosion/explosion_00027.jpg \
    resources/images/clips/explosion/explosion_00026.jpg \
    resources/images/clips/explosion/explosion_00025.jpg \
    resources/images/clips/explosion/explosion_00024.jpg \
    resources/images/clips/explosion/explosion_00023.jpg \
    resources/images/clips/explosion/explosion_00022.jpg \
    resources/images/clips/explosion/explosion_00021.jpg \
    resources/images/clips/explosion/explosion_00020.jpg \
    resources/images/clips/explosion/explosion_00019.jpg \
    resources/images/clips/explosion/explosion_00018.jpg \
    resources/images/clips/explosion/explosion_00017.jpg \
    resources/images/clips/explosion/explosion_00016.jpg \
    resources/images/clips/explosion/explosion_00015.jpg \
    resources/images/clips/explosion/explosion_00014.jpg \
    resources/images/clips/explosion/explosion_00013.jpg \
    resources/images/clips/explosion/explosion_00012.jpg \
    resources/images/clips/explosion/explosion_00011.jpg \
    resources/images/clips/explosion/explosion_00010.jpg \
    resources/images/clips/explosion/explosion_00009.jpg \
    resources/images/clips/explosion/explosion_00008.jpg \
    resources/images/clips/explosion/explosion_00007.jpg \
    resources/images/clips/explosion/explosion_00006.jpg \
    resources/images/clips/explosion/explosion_00005.jpg \
    resources/images/clips/explosion/explosion_00004.jpg \
    resources/images/clips/explosion/explosion_00003.jpg \
    resources/images/clips/explosion/explosion_00002.jpg \
    resources/images/clips/explosion/explosion_00001.jpg \
    resources/images/clips/biochem/biochem_00046.jpg \
    resources/images/clips/biochem/biochem_00045.jpg \
    resources/images/clips/biochem/biochem_00044.jpg \
    resources/images/clips/biochem/biochem_00043.jpg \
    resources/images/clips/biochem/biochem_00042.jpg \
    resources/images/clips/biochem/biochem_00041.jpg \
    resources/images/clips/biochem/biochem_00040.jpg \
    resources/images/clips/biochem/biochem_00039.jpg \
    resources/images/clips/biochem/biochem_00038.jpg \
    resources/images/clips/biochem/biochem_00037.jpg \
    resources/images/clips/biochem/biochem_00036.jpg \
    resources/images/clips/biochem/biochem_00035.jpg \
    resources/images/clips/biochem/biochem_00034.jpg \
    resources/images/clips/biochem/biochem_00033.jpg \
    resources/images/clips/biochem/biochem_00032.jpg \
    resources/images/clips/biochem/biochem_00031.jpg \
    resources/images/clips/biochem/biochem_00030.jpg \
    resources/images/clips/biochem/biochem_00029.jpg \
    resources/images/clips/biochem/biochem_00028.jpg \
    resources/images/clips/biochem/biochem_00027.jpg \
    resources/images/clips/biochem/biochem_00026.jpg \
    resources/images/clips/biochem/biochem_00025.jpg \
    resources/images/clips/biochem/biochem_00024.jpg \
    resources/images/clips/biochem/biochem_00023.jpg \
    resources/images/clips/biochem/biochem_00022.jpg \
    resources/images/clips/biochem/biochem_00021.jpg \
    resources/images/clips/biochem/biochem_00020.jpg \
    resources/images/clips/biochem/biochem_00019.jpg \
    resources/images/clips/biochem/biochem_00018.jpg \
    resources/images/clips/biochem/biochem_00017.jpg \
    resources/images/clips/biochem/biochem_00016.jpg \
    resources/images/clips/biochem/biochem_00015.jpg \
    resources/images/clips/biochem/biochem_00014.jpg \
    resources/images/clips/biochem/biochem_00013.jpg \
    resources/images/clips/biochem/biochem_00012.jpg \
    resources/images/clips/biochem/biochem_00011.jpg \
    resources/images/clips/biochem/biochem_00010.jpg \
    resources/images/clips/biochem/biochem_00009.jpg \
    resources/images/clips/biochem/biochem_00008.jpg \
    resources/images/clips/biochem/biochem_00007.jpg \
    resources/images/clips/biochem/biochem_00006.jpg \
    resources/images/clips/biochem/biochem_00005.jpg \
    resources/images/clips/biochem/biochem_00004.jpg \
    resources/images/clips/biochem/biochem_00003.jpg \
    resources/images/clips/biochem/biochem_00002.jpg \
    resources/images/clips/biochem/biochem_00001.jpg

