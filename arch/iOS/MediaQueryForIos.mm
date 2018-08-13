/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** Replacement for (not perfectly functional) QStandardPaths MusicLocation type
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#import <MediaPlayer/MediaPlayer.h>

#include <QStringList>


const QStringList
v4m_ios_media_query()
{
  QStringList result;
  MPMediaQuery *musicQuery = [[[MPMediaQuery alloc] init] songs];

  for (auto piece : [musicQuery items])
    result << piece;

  return result;
}
