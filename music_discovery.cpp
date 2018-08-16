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
#include <QDirIterator>

#include "music_discovery.h"

MusicDiscovery::MusicDiscovery(const QDir &r, const QStringList &sl)
        : m_rootDir(r), m_standardMusicLocations(sl)
{
}

void
MusicDiscovery::reload()
{
    QDirIterator it(":/music/", QDirIterator::Subdirectories);

    m_musicFilePaths.clear();
    while (it.hasNext())
    {
        QString next_work(it.next());

        m_musicFilePaths << next_work;
    }
}

const QList<QUrl>
MusicDiscovery::localMusicUrls()
{
  QList<QUrl> urls;

  for(auto path : musicFilePaths())
  {
    // we need to remove the stupid ':' in front
    QString url("qrc:///" + path.remove(0,2));
    urls << url;
  }

  return urls;
}
