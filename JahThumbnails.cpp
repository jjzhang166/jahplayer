//
//  This file is part of Jahshaka
//  Copyright (c) 2016 Sputnik7 (MIT)
//
//  This is free software: you may copy, redistribute
//  and/or modify it under the terms of the MIT License
//

#include "JahSettings.h"
#include "JahException.h"
#include "JahThumbnails.h"

#include <QDir>
#include <QMessageBox>
#include <QListWidgetItem>

JahThumbnails::JahThumbnails(QWidget *parent)
    : QListWidget(parent)
{
    try {
        database = new JahDatabase(this);
        initFromDb();
    }
    catch(JahException &e) {
        QMessageBox::critical(this, tr("Error"), e.message);
    }

    setViewMode(IconMode);
    setIconSize(QSize(200, 200));
    setResizeMode(Adjust);
}

JahImageSequence* JahThumbnails::current() {
    auto p = currentIndex().row();
    return p >= 0 && p < sequences.size() ? sequences[p] : 0;
}

JahImageSequence *JahThumbnails::fromUrl(QUrl url) {
    for (auto s: sequences)
        if (s->reference == url)
            return s;
    throw JahException(tr("no definition for %1").arg(url.toString()));
}

void JahThumbnails::initFromFolder() {
    JahSettings s;
    auto base = s.folderImages;
    QDir dir(base);
    for (auto f: dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name)) {
        auto s = new JahImageSequence;
        sequences << s;
        s->loadFromFolder(base + '/' + f);
        addItem(new QListWidgetItem(QPixmap::fromImage(s->thumbnail()), f));
    }
}

void JahThumbnails::initFromDb() {
    for (auto d: database->allDefinitions()) {
        auto s = new JahImageSequence;
        sequences << s;
        s->setSequence(d.id, d.files);
        addItem(new QListWidgetItem(QPixmap::fromImage(s->thumbnail()), d.id.name()));
    }
}
