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

MusicDiscovery::MusicDiscovery(const QDir &r, const QStringList &sl) : m_root_dir(r), m_standard_music_locations(sl) {}

static void
recursiveDiscovery(QDir &startDir, const QStringList &music_file_filters, QStringList &result)
{
   if (!startDir.exists())
      qWarning("\tCannot find the %s directory", qPrintable(startDir.path()));
   else
   {
       QStringList subdir_names = startDir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
       startDir.setNameFilters(music_file_filters);
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
         recursiveDiscovery(subdir, music_file_filters, result);
       }
   }
}

void
MusicDiscovery::reload()
{
    QStringList music_file_filters;
    //
    // FIXME: this is an ugly hack: file formats should not be hard-wired in the code
    //
    music_file_filters << "*.mp3"<< "*.ogg" << "*.flac" << "*.aac" << "*.ac3" << "*.aiff" << "*.aif" << "*.m4a" << "*.wav" << "*.wma";

    for (auto music_location : m_standard_music_locations)
    {
      QDir mpath(music_location);

      if (mpath.isRelative())
      {
        QString musicFullPath = m_root_dir.path() + QLatin1String("/") + music_location;

        mpath.setPath(musicFullPath);
      }

      recursiveDiscovery(mpath, music_file_filters, m_music_file_paths);
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
