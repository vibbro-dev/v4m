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

static void
recursiveDiscovery(QDir &startDir, const QStringList &music_file_filters, QStringList &result)
{
   qInfo() << "***** visiting directory:" << startDir.path();
   if (!startDir.exists())
      qFatal("\tCannot find the %s directory", qPrintable(startDir.path()));

   QStringList subdir_names = startDir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
   startDir.setNameFilters(music_file_filters);
   //
   // read the music files in the current directory first...
   //
   for (auto music_file_name : startDir.entryList())
     result += (startDir.path() + "/" + music_file_name);

   //
   // and then recurse in the subdirectories
   //
   for (auto subdir_name : subdir_names)
   {
     QDir subdir(startDir.path() + "/" + subdir_name);
     recursiveDiscovery(subdir, music_file_filters, result);
   }
}

const QStringList 
musicDiscovery()
{
    // switch to QDir and do it the hard way
    qInfo() << "\nUsing QDir class capabilities...";
    QString musicFullPath = QDir::homePath() + "/" + QStandardPaths::displayName(QStandardPaths::MusicLocation);
    qInfo() << "\tMusic full path is (string): " << musicFullPath;
    QDir music(musicFullPath);

    QStringList music_file_filters;
    music_file_filters << "*.mp3"<< "*.ogg" << "*.flac" << "*.aac" << "*.ac3" << "*.aiff" << "*.aif" << "*.m4a" << "*.wav" << "*.wma" << "*.ogv";

    QStringList music_files;

    recursiveDiscovery(music, music_file_filters, music_files);

    return music_files;
}
