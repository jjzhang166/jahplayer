//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHHISTOGRAMWIDGET_H
#define JAHHISTOGRAMWIDGET_H

#include <QWidget>
#include <QThread>
#include <QVideoFrame>

class JahFrameProcessor: public QObject
{
    Q_OBJECT

public slots:
    void processFrame(QVideoFrame frame, int levels);

signals:
    void histogramReady(QVector<qreal> histogram);
};

class JahHistogramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JahHistogramWidget(QWidget *parent = 0);

    ~JahHistogramWidget();
    void setLevels(int levels) { m_levels = levels; }

public slots:
    void processFrame(QVideoFrame frame);
    void setHistogram(QVector<qreal> histogram);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<qreal> m_histogram;
    int m_levels;
    JahFrameProcessor m_processor;
    QThread m_processorThread;
    bool m_isBusy;
};

#endif // JAHHISTOGRAMWIDGET_H
