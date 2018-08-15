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
#include <QResource>
#include <QDirIterator>

#include "music_discovery.h"

MusicDiscovery::MusicDiscovery(const QDir &r, const QStringList &sl)
        : m_rootDir(r), m_standardMusicLocations(sl)
{
}

void
MusicDiscovery::reload()
{
    QResource::registerResource("./music.rcc");
    QDirIterator it(":/music/", QDirIterator::Subdirectories);

    m_musicFilePaths.clear();
    while (it.hasNext())
    {
        QString next_work(it.next());

        qInfo() << next_work;
        m_musicFilePaths << next_work;
    }
}

const QList<QUrl>
MusicDiscovery::localMusicUrls()
{
  QList<QUrl> urls;

  for(auto path : musicFilePaths())
    urls << path;

  return urls;
}
