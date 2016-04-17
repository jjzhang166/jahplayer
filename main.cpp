//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/jahplayer-icon.png"));

    QSplashScreen splash(QPixmap(":/resources/jahplayer-logo.jpg"));
    splash.show();
    splash.showMessage(splash.tr("Welcome to JahPlayer\nby Sputnik7"));

    QTimer::singleShot(10000, [&splash]() { splash.close(); });
    app.processEvents();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
