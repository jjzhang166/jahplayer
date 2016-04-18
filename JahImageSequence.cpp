//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahImageSequence.h"

#include <QtConcurrent>
#include <QDir>

using namespace QtConcurrent;

JahImageSequence::JahImageSequence(QObject *parent) : QObject(parent) {

}

void JahImageSequence::loadFromFolder(QString folder) {

    QDir dir(folder);
    for (auto name : dir.entryList({"*.jpg", "*.BMP"}, QDir::Files, QDir::Name))
         cache << frame { name, QImage() };

    if (cache.size())
        cache[curr = 0].load(folder);
}

void JahImageSequence::start() {
    auto fw = new QFutureWatcher<void>;
    connect(fw, &QFutureWatcher<void>::finished, [this, fw]() {
        emit ready();
        curr = 0;
        fw->deleteLater();
    });
    fw->setFuture(QtConcurrent::map(cache, [this](frame &f) { f.load(reference.path()); }));
}

bool JahImageSequence::frame::load(QString folder) {
    if (data.isNull()) {
        auto r = data.load(folder + '/' + name);
        if (!r)
            qDebug() << r << (folder + '/' + name) << data;
    }
    return !data.isNull();
}

bool JahImageSequence::finished() const {
    return curr == cache.size();
}

QImage JahImageSequence::next() {
    if (curr >= 0 && curr < cache.size()) {
        auto i = cache[curr].data;
        if (!i.isNull()) {
            ++curr;
            return i;
        }
    }
    return QImage();
}

QImage JahImageSequence::thumbnail() {
    if (curr >= 0)
        return cache[0].data;
    return QImage();
}

void JahImageSequence::setSequence(JahIdMedia id, QStringList images) {
    reference = id;

    auto p = reference.path();
    for (auto i : images)
        cache << frame { i, QImage() };

    if (cache.size())
        cache[curr = 0].load(p);
}

void JahImageSequence::setCurrentFrame(int frame) {
    if (frame >= 0 && frame < totFrames())
        curr = frame;
}
