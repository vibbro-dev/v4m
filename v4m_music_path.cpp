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
#include <QStandardPaths>

#if !defined(Q_OS_LINUX)

#   define _V4M_OS_MUSIC_PATHS_ (QStandardPaths::standardLocations(QStandardPaths::MusicLocation))

#endif /* !defined(Q_OS_LINUX) */

#if defined(Q_OS_LINUX)

#include <QTranslator>

#   define _V4M_OS_MUSIC_PATHS_ (QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0) + QLatin1String("/") + QObject::tr("Music"))

#endif /* defined(Q_OS_LINUX) */

const QStringList &musicLocationPath()
{
   static QStringList result;

   result.clear();
   result << _V4M_OS_MUSIC_PATHS_;

   qInfo() << "*** standard music paths found:";
   for (auto path : result)
       qInfo() << "\t" << path;

   return result;
}
