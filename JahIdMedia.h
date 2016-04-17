//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHIDMEDIA_H
#define JAHIDMEDIA_H

#include <QUrl>

/**
 * @brief The JahIdMedia class
 *  identify a media (sequence of images)
 *  store all info required to play
 */
class JahIdMedia : public QUrl
{
public:

    /**
     * @brief jah_scheme
     *  arbitrary unique identifier for media object
     * @return
     *  fixed media object scheme
     */
    static QString jah_scheme() { return "jah"; }

    /**
     * @brief jah_host
     *  arbitrary unique identifier for media object
     * @return
     *  fixed media object host
     */
    static QString jah_host() { return "player"; }

    JahIdMedia();
    JahIdMedia(const JahIdMedia& other);
    JahIdMedia(QString folder, QString name, int media, int frameStart, int frameEnd);

    int media() const;
    int frameStart() const;
    int frameEnd() const;

    QString path() const;
    QString name() const;

    QString imagePath() const;

    static QString namePatternFromNumeric(QString fileNumber, QString fileNonum);
    static QString namePatternAssignNumber(QString filePattern, int number, QString fileExt);

private:

    void defineUrl(QString path = "", QString name = "", int media = 0, int frameStart = 0, int frameEnd = 0);
};

#endif // JAHIDMEDIA_H
