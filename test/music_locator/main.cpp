/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** This small app is just to test the file location capabilities within Qt
** The target is to be able to locate all music files within a given device
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#include <QDebug>

#include "music_discovery.h"

int
main(int /* not used */, char */* not used either */[])
{
    MusicDiscovery default_music;

    default_music.reload();

    qInfo() << "Music Files found:";
    for (const auto s : default_music.musicFilePaths())
      qInfo() << "\t" << s;
}
