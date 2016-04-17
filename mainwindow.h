//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/**
 * @brief The MainWindow class
 *  standard UI for minimal test case
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    void setupQtMedia();
    void setupJahMedia();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
