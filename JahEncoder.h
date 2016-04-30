//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#ifndef JAHENCODER_H
#define JAHENCODER_H

//! from http://roxlu.com/2013/010/x264-encoder

#include <QObject>
#include <QVideoFrame>

extern "C" {
#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
}

#undef PixelFormat

/**
 * @brief The JahEncoder class
 *  Simple wrapper for x264 that you can use to encode into x264.
 *  Make sure to set all the params before calling `open()`.
 *  See below for the members that the you need to set.
 */
class JahEncoder : public QObject
{
    Q_OBJECT

public:
    explicit JahEncoder(QObject *parent = 0);
    virtual ~JahEncoder();

    //! open for encoding
    bool open(QString filename);

    //! close the encoder and file, frees all memory
    bool close();

signals:

public slots:

    void encode(QVideoFrame videoframe);

private:

    //! validates if all params are set correctly, like width,height, etc..
    bool validateSettings();

    //! sets the x264 params
    void setParams();

    //! depending on configuration, either throw or issue qFatal
    bool fatal(QString why);

    //! encode the given data
    bool encode_pixels(char* pixels);

public:

    //! params the user should set
    int in_width = 0;
    int in_height = 0;
    int out_width = 0;
    int out_height = 0;

    //! e.g. 25, 60, etc..
    int fps = 25;
    AVPixelFormat in_pixel_format = AV_PIX_FMT_NONE;
    AVPixelFormat out_pixel_format = AV_PIX_FMT_NONE;

    /* x264 */

    //! used for our "raw" input container
    AVPicture pic_raw;
    x264_picture_t pic_in;
    x264_picture_t pic_out;
    x264_param_t params;
    x264_nal_t* nals;
    x264_t* encoder = nullptr;
    int num_nals = 0;

    //! input / output
    int pts = 0;
    SwsContext* sws = nullptr;
    FILE* fp = nullptr;
};

#endif // JAHENCODER_H
