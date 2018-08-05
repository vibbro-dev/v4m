/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** Auto-discovery of music files (the hard way)
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#if !defined(_V4M_MUSIC_DISCOVERY_H_)
# define _V4M_MUSIC_DISCOVERY_H_

#include <QString>
#include <QStringList>
#include <QDir>
#include <QStandardPaths>
#include <QUrl>

#include "v4m_music_path.h"

class MusicDiscovery
{
public:
    explicit MusicDiscovery(const QDir &root = QDir::homePath(), const QStringList &standard_locations = musicLocationPath());
    const QStringList musicFilePaths()          { return m_music_file_paths; }
    const QList<QUrl> localMusicUrls();
    void reload();

private:

    const QDir &m_root_dir;
    const QStringList &m_standard_music_locations;
    QStringList m_music_file_paths;
};

#endif /* !defined(_V4M_MUSIC_DISCOVERY_H_) */
