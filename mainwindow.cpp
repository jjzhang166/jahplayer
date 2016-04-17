//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "mainwindow.h"

#include <QDebug>
#include <QMenuBar>
#include <QSplitter>

#include <QMediaPlayer>
#include <QVideoWidget>

#include "JahMediaPlayer.h"
#include "JahVideoWidget.h"

#include "JahSettings.h"
#include "JahThumbnails.h"
#include "JahPlayerUIControls.h"

void MainWindow::setupQtMedia()
{
    auto v = new QVideoWidget;
    setCentralWidget(v);

    auto p = new QMediaPlayer;
    p->setVideoOutput(v);

    auto start = menuBar()->addAction("start");
    connect(start, &QAction::triggered, [p]() {
        qDebug() << "start";
        p->setMedia(QUrl::fromLocalFile("/home/carlo/Videos/my/rosaspina/P1090585.MOV"));
        p->play();
    });

    auto stop = menuBar()->addAction("stop");
    connect(stop, &QAction::triggered, [p]() {
        qDebug() << "stop";
        p->stop();
    });
}

void MainWindow::setupJahMedia() {

    auto s = new QSplitter(Qt::Vertical);
    s->setHandleWidth(3);
    setCentralWidget(s);

    auto v = new JahVideoWidget;
    s->addWidget(v);

    auto c = new JahPlayerUIControls;
    s->addWidget(c);

    auto l = new JahThumbnails;
    s->addWidget(l);

    auto p = new JahMediaPlayer;
    p->setVideoOutput(v);

    v->setThumbnails(l);

    c->routeBehaviour(p);
    /*
    connect(c->Play, &QAbstractButton::clicked, [p, l]() {
        if (auto i = l->current()) {
            i->start();
            p->setMedia(l->current()->reference); //QUrl::fromLocalFile(l->current()->folder));
            p->play();
        }
    });

    connect(c->Stop, &QAbstractButton::clicked, [p]() {
        p->stop();
    });
    */
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    JahSettings settings;
    settings.loadGeometry(this);
    //setupQtMedia();
    setupJahMedia();
}

MainWindow::~MainWindow()
{
    JahSettings settings;
    settings.saveGeometry(this);
}
