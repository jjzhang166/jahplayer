//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahEncoder.h"
#include "JahException.h"
#include <QDebug>

#include <inttypes.h>
#include <stdio.h>

JahEncoder::JahEncoder(QObject *parent) : QObject(parent) {
    memset(&pic_raw, 0, sizeof(pic_raw));
}

JahEncoder::~JahEncoder() {
    if (sws)
        close();
}

bool JahEncoder::open(QString filename) {

    if (!validateSettings()) {
        return false;
    }

    int r = 0;
    int nheader = 0;
    int header_size = 0;

    // @todo add validate which checks if all params are set (in/out width/height, fps,etc..);
    if (encoder)
        return fatal(tr("Already opened. first call close()"));

    if (out_pixel_format != AV_PIX_FMT_YUV420P)
        return fatal(tr("At this moment the output format must be AV_PIX_FMT_YUV420P"));

    sws = sws_getContext(in_width, in_height, in_pixel_format,
                         out_width, out_height, out_pixel_format,
                         SWS_FAST_BILINEAR, NULL, NULL, NULL);

    if (!sws)
        return fatal(tr("Cannot create SWS context"));

    fp = fopen(filename.toUtf8(), "w+b");
    if (!fp)
        return fatal(tr("Cannot open the h264 destination file"));

    x264_picture_alloc(&pic_in, X264_CSP_I420, out_width, out_height);

    setParams();

    // create the encoder using our params
    encoder = x264_encoder_open(&params);
    if (!encoder)
        return fatal(tr("Cannot open the encoder"));

    // write headers
    r = x264_encoder_headers(encoder, &nals, &nheader);
    if (r < 0)
        return fatal(tr("x264_encoder_headers() failed"));

    header_size = nals[0].i_payload + nals[1].i_payload + nals[2].i_payload;
    if (!fwrite(nals[0].p_payload, header_size, 1, fp))
        return fatal(tr("Cannot write headers"));

    pts = 0;

    return true;
}

bool JahEncoder::encode_pixels(char* pixels) {
    if (!sws)
        return fatal(tr("Not initialized, so cannot encode"));

    // copy the pixels into our "raw input" container.
    int bytes_filled = avpicture_fill(&pic_raw, (uint8_t*)pixels, in_pixel_format, in_width, in_height);
    if (!bytes_filled)
        return fatal(tr("Cannot fill the raw input buffer"));

    // convert to I420 for x264
    int h = sws_scale(sws, pic_raw.data, pic_raw.linesize, 0,
                      in_height, pic_in.img.plane, pic_in.img.i_stride);

    if (h != out_height)
        return fatal(tr("scale failed: %1").arg(h));

    // and encode and store into pic_out
    pic_in.i_pts = pts;

    int frame_size = x264_encoder_encode(encoder, &nals, &num_nals, &pic_in, &pic_out);
    if (frame_size) {
        if (!fwrite(nals[0].p_payload, frame_size, 1, fp))
            return fatal(tr("Error while trying to write nal"));
    }
    ++pts;

    return true;
}

bool JahEncoder::close() {
    if (encoder) {
        x264_picture_clean(&pic_in);
        memset(&pic_in, 0, sizeof(pic_in));
        memset(&pic_out, 0, sizeof(pic_out));

        x264_encoder_close(encoder);
        encoder = NULL;
    }

    if (sws) {
        sws_freeContext(sws);
        sws = NULL;
    }

    memset(&pic_raw, 0, sizeof(pic_raw));

    if (fp) {
        fclose(fp);
        fp = NULL;
    }
    return true;
}

void JahEncoder::setParams() {
    x264_param_default_preset(&params, "ultrafast", "zerolatency");
    params.i_threads = 1;
    params.i_width = out_width;
    params.i_height = out_height;
    params.i_fps_num = fps;
    params.i_fps_den = 1;
}

bool JahEncoder::validateSettings() {
    if (!in_width)
        return fatal(tr("No in_width set"));
    if (!in_height)
        return fatal(tr("No in_height set"));
    if (!out_width)
        return fatal(tr("No out_width set"));
    if (!out_height)
        return fatal(tr("No out_height set"));
    if (in_pixel_format == AV_PIX_FMT_NONE)
        return fatal(tr("No in_pixel_format set"));
    if (out_pixel_format == AV_PIX_FMT_NONE)
        return fatal(tr("No out_pixel_format set"));
    return true;
}

bool JahEncoder::fatal(QString why) {
    throw JahException(why);
    return false;
}

void JahEncoder::encode(QVideoFrame videoframe) {
    if (videoframe.isMapped())
        encode_pixels((char*)(videoframe.bits()));
}
