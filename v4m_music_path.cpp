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

#include <QStandardPaths>

#if !defined(Q_OS_LINUX)

const QStringList &musicLocationPath()
{
   return QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
}

#endif /* !defined(Q_OS_LINUX) */

#if defined(Q_OS_LINUX)

#include <QTranslator>

const QStringList &musicLocationPath()
{
  static QStringList result;

  result << (QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0) + QLatin1String("/") + QObject::tr("Music"));

  return result;
}

#endif /* defined(Q_OS_LINUX) */
