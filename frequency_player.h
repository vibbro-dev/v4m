/****************************************************************************
**
** Copyright (C) 2018 Vibbro
**
** This file is licensed under the GNU/GPL License version 3.0
**
****************************************************************************/

#ifndef FREQUENCY_PLAYER_H
#define FREQUENCY_PLAYER_H

#include <QWidget>

#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
class QStatusBar;
QT_END_NAMESPACE

#if 0
QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QStatusBar;
class QVideoProbe;
class QVideoWidget;
class QAudioProbe;
QT_END_NAMESPACE
#endif


class FrequencyPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyPlayer(QWidget *parent = nullptr);
    ~FrequencyPlayer();

    bool isPlayerAvailable() const;

    void addToPlaylist(const QList<QUrl> &urls);

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
#if 0
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void metaDataChanged();
#endif

    void jump(const int index);
    void play(const int fid);
#if 0
    void playlistPositionChanged(int);
#endif

    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void bufferingProgress(int progress);

    void displayErrorMessage();

private:

    void setStatusInfo(const QString &info);

    QMediaPlayer *m_player = nullptr;
    QMediaPlaylist *m_playlist = nullptr;
#if 0
    QLabel *m_coverLabel = nullptr;
    QSlider *m_slider = nullptr;
    QLabel *m_labelDuration = nullptr;
    QLabel *m_statusLabel = nullptr;
#endif
    QStatusBar *m_statusBar = nullptr;

#if 0
    PlaylistModel *m_playlistModel = nullptr;
    QAbstractItemView *m_playlistView = nullptr;
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
#endif
};

#endif // FREQUENCY_PLAYER_H
