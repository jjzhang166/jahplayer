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
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

#include "JahSettings.h"
#include "JahThumbnails.h"
#include "JahMediaPlayer.h"
#include "JahVideoWidget.h"
#include "JahPlayerUIControls.h"

void MainWindow::setupJahMedia() {

    auto s = new QSplitter(Qt::Vertical);
    s->setHandleWidth(3);
    setCentralWidget(s);

    auto v = videoWidget = new JahVideoWidget;
    s->addWidget(v);

    auto c = new JahPlayerUIControls;
    s->addWidget(c);

    auto l = new JahThumbnails;
    s->addWidget(l);

    auto p = new JahMediaPlayer;
    p->setVideoOutput(v);

    v->setThumbnails(l);

    c->routeBehaviour(p);
}

void MainWindow::setupCommands() {
    auto commands = menuBar()->addMenu(tr("Commands"));

    auto selectDb = commands->addAction(tr("Select Db..."));
    selectDb->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    connect(selectDb, &QAction::triggered, [&]() {
        JahSettings settings;
        QFileDialog fd(this, tr("Open or Create Db"), settings.sqlitePath);
        fd.setNameFilters({tr("Jahshaka databases (*.jahdb)"), tr("Any file (*)")});
        fd.setFileMode(QFileDialog::AnyFile);
        fd.setViewMode(QFileDialog::Detail);
        fd.setHistory(settings.openDbHistory);
        if (fd.exec()) {
            auto l = fd.selectedFiles();
            if (l.size() == 1) {
                auto dir = fd.directory();
                settings.openDbHistory = fd.history();
                settings.sqlitePath = dir.absolutePath();
                settings.sqliteName = dir.relativeFilePath(l[0]);
                settings.save();
                videoWidget->getThumbnails()->connectToDb();
            }
        }
    });

    auto addAssetDirToDb = commands->addAction(tr("Add Asset to Db..."));
    addAssetDirToDb->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    connect(addAssetDirToDb, &QAction::triggered, [&]() {
        JahSettings settings;
        QFileDialog fd(this, tr("Select a folder of image sequence"), settings.folderImages);
        fd.setNameFilters({tr("Image Folder")});
        fd.setFileMode(QFileDialog::DirectoryOnly);
        fd.setViewMode(QFileDialog::Detail);
        fd.setHistory(settings.openDbHistory);
        if (fd.exec()) {
            settings.openDbHistory = fd.history();
            settings.folderImages = fd.directory().absolutePath();
            settings.save();
            videoWidget->getThumbnails()->addAssetDirToDb(settings.folderImages);
        }
    });

    //auto createDb = commands->addAction(tr("selectDb"));SP_DialogSaveButton

    auto histogram = commands->addAction(tr("Histogram"));
    histogram->setCheckable(true);

    connect(histogram, &QAction::toggled, [&](bool checked) {
        if (checked)
            videoWidget->displayHistogram();
        else
            videoWidget->removeHistogram();
    });

    auto encode = commands->addAction(tr("Encode..."));
    encode->setCheckable(true);
    connect(encode, &QAction::toggled, [&](bool checked) {
        if (checked) {
            videoWidget->enableEncoding("/tmp/x.mov");
        }
        else
            videoWidget->disableEncoding();
    });
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    JahSettings settings;
    settings.loadGeometry(this);
    setupJahMedia();
    setupCommands();
}

MainWindow::~MainWindow()
{
    JahSettings settings;
    settings.saveGeometry(this);
}
