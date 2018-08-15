/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** Replacement for (not perfectly functional) QStandardPaths MusicLocation type
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#include "v4m_music_path.h"

#include <QDebug>
#include <QDir>

const QStringList &musicLocationPath()
{
   static QStringList result;

   result.clear();
   result << (QDir::currentPath() + QLatin1String("/music"));

#if 0
   qInfo() << "*** standard music paths found:";
   for (auto path : result)
       qInfo() << "\t" << path;
#endif

   return result;
}
