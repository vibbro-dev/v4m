/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** Auto-discovery of music files (the hard way)
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#include <QDebug>

#include "music_discovery.h"

MusicDiscovery::MusicDiscovery(const QDir &r, const QStringList &sl)
        : m_rootDir(r), m_standardMusicLocations(sl)
{
}

static void
recursiveDiscovery(QDir &startDir, const QStringList &musicFileFilters, QStringList &result)
{
   if (!startDir.exists())
      qWarning("\tCannot find the %s directory", qPrintable(startDir.path()));
   else
   {
       QStringList subdir_names = startDir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
       startDir.setNameFilters(musicFileFilters);
       //
       // read the music files in the current directory first...
       //
       for (auto music_file_name : startDir.entryList())
         result += (startDir.path() + QLatin1String("/") + music_file_name);
    
       //
       // and then recurse in the subdirectories
       //
       for (auto subdir_name : subdir_names)
       {
         QDir subdir(startDir.path() + QLatin1String("/") + subdir_name);
         recursiveDiscovery(subdir, musicFileFilters, result);
       }
   }
}

void
MusicDiscovery::reload()
{
    m_musicFilePaths.clear();
    //
    // FIXME: this is an ugly hack: file formats should not be hard-wired in the code
    //
    QStringList musicFileFilters;
    musicFileFilters << "*.mp3"<< "*.ogg" << "*.flac" << "*.aac" << "*.ac3" << "*.aiff" << "*.aif" << "*.m4a" << "*.wav" << "*.wma";

    for (auto music_location : musicLocationPath())
    {
      QDir mpath(music_location);

      if (mpath.isRelative())
      {
        QString musicFullPath = m_rootDir.path() + QLatin1String("/") + music_location;

        mpath.setPath(musicFullPath);
      }

      recursiveDiscovery(mpath, musicFileFilters, m_musicFilePaths);
    }
}

const QList<QUrl>
MusicDiscovery::localMusicUrls()
{
  QList<QUrl> urls;

  for(auto path : musicFilePaths())
    urls << QUrl("file:///" + path);

  return urls;
}
