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
#include <QStandardPaths>
#include <QDir>

#include "music_discovery.h"

int
main(int /* not used */, char */* not used either */[])
{
    // see if we're somewhere close
    qInfo() << "Music Location is (enum): " << quint32(QStandardPaths::MusicLocation);
    qInfo() << "Music Location is (string): " << QStandardPaths::displayName(QStandardPaths::MusicLocation);

    // check if the locateAll static method works (it usually _doesn't_)
    qInfo() << "\nUsing QStandardPaths::locateAll() function...";
    qInfo() << "\tMusic files found: " << QStandardPaths::locateAll(QStandardPaths::MusicLocation, "*.mp3");

    // switch to QDir and do it the hard way
    qInfo() << "\nUsing QDir class capabilities...";
    
    QStringList music_files = musicDiscovery();

    qInfo() << "\tFiles found:";
    for (const auto s : music_files)
      qInfo() << "\t\t" << s;
}
