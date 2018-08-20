/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc
**
** Licensed under the terms of the GNU GPL version 3 License
**
****************************************************************************/

#include "frequency_player.h"
#include "frequency_player_controls.h"

#if 0
#include "playercontrols.h"
#include "playlistmodel.h"
#include "histogramwidget.h"
#include "videowidget.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#endif
#include <QMediaMetaData>

#include <QtWidgets>

FrequencyPlayer::FrequencyPlayer(QWidget *parent)
    : QWidget(parent)
{
//! [create-objs]
    m_player = new QMediaPlayer(this);
    m_player->setAudioRole(QAudio::MusicRole);
    m_playlist = new QMediaPlaylist();
    m_player->setPlaylist(m_playlist);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

#if 0
    qInfo() << "Supported audio roles:";
    for (QAudio::Role role : m_player->supportedAudioRoles())
        qInfo() << "    " << role;
    // owned by PlaylistModel
//! [create-objs]

    connect(m_player, &QMediaPlayer::durationChanged, this, &FrequencyPlayer::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &FrequencyPlayer::positionChanged);
    connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &FrequencyPlayer::metaDataChanged);
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &FrequencyPlayer::playlistPositionChanged);
#endif
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &FrequencyPlayer::statusChanged);
    connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &FrequencyPlayer::bufferingProgress);
    connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &FrequencyPlayer::displayErrorMessage);
    connect(m_player, &QMediaPlayer::stateChanged, this, &FrequencyPlayer::stateChanged);

#if 0
//! [2]
    m_playlistModel = new PlaylistModel(this);
    m_playlistModel->setPlaylist(m_playlist);
//! [2]

    m_playlistView = new QListView(this);
    m_playlistView->setModel(m_playlistModel);
    m_playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));

    connect(m_playlistView, &QAbstractItemView::activated, this, &FrequencyPlayer::jump);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, m_player->duration() / 1000);
#endif

#if 0
    m_labelDuration = new QLabel(this);
    connect(m_slider, &QSlider::sliderMoved, this, &FrequencyPlayer::seek);

    m_labelHistogram = new QLabel(this);
    m_labelHistogram->setText("Histogram:");
    m_videoHistogram = new HistogramWidget(this);
    m_audioHistogram = new HistogramWidget(this);
    QHBoxLayout *histogramLayout = new QHBoxLayout;
    histogramLayout->addWidget(m_labelHistogram);
    histogramLayout->addWidget(m_videoHistogram, 1);
    histogramLayout->addWidget(m_audioHistogram, 2);

    m_videoProbe = new QVideoProbe(this);
    connect(m_videoProbe, &QVideoProbe::videoFrameProbed, m_videoHistogram, &HistogramWidget::processFrame);
    m_videoProbe->setSource(m_player);

    m_audioProbe = new QAudioProbe(this);
    connect(m_audioProbe, &QAudioProbe::audioBufferProbed, m_audioHistogram, &HistogramWidget::processBuffer);
    m_audioProbe->setSource(m_player);

    QPushButton *openButton = new QPushButton(tr("Open"), this);

    connect(openButton, &QPushButton::clicked, this, &FrequencyPlayer::open);
#endif

    FrequencyPlayerControls *controls = new FrequencyPlayerControls(this);

    connect(controls, &FrequencyPlayerControls::play, this, &FrequencyPlayer::play);
#if 0
    for (quint k = 0; k < controls->numberOfFrequencyControls(); ++k)
    {
      controls[k]->setState(m_player->state());
      controls[k]->setVolume(m_player->volume());
      controls[k]->setMuted(controls->isMuted());

      connect(controls[k], &FrequencyControl::play, this, &FrequencyPlayer::play);
      connect(controls[k], &FrequencyControl::stop, this, &FrequencyPlayer::stop);

      connect(controls[k], &FrequencyControl::changeVolume, this, &FrequencyPlayer::setVolume);
      connect(controls[k], &FrequencyControl::changeMuting, this, &FrequencyPlayer::setMuted);
    }
#endif

    connect(m_player, &QMediaPlayer::stateChanged, controls, &FrequencyPlayerControls::setState);
    connect(m_player, &QMediaPlayer::volumeChanged, controls, &FrequencyPlayerControls::setVolume);

    QBoxLayout *controlLayout = new QVBoxLayout(this);
    controlLayout->setMargin(0);
    controlLayout->addWidget(controls);

    setLayout(controlLayout);
}

FrequencyPlayer::~FrequencyPlayer()
{
}

bool FrequencyPlayer::isPlayerAvailable() const
{
    return m_player->isAvailable();
}

#if 0
void FrequencyPlayer::open()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    QStringList supportedMimeTypes = m_player->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    qInfo() << "Music Directory: " << QStandardPaths::displayName(QStandardPaths::MusicLocation);
    qInfo() << "Music files found: " << QStandardPaths::locateAll(QStandardPaths::MusicLocation, "*.mp3");
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls());
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}
#endif

void FrequencyPlayer::addToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) {
#if 0
        if (isPlaylist(url))
            m_playlist->load(url);
        else
            m_playlist->addMedia(url);
#endif
        m_playlist->addMedia(url);
    }
}

#if 0
void FrequencyPlayer::setCustomAudioRole(const QString &role)
{
    m_player->setCustomAudioRole(role);
}

void FrequencyPlayer::durationChanged(qint64 duration)
{
    m_duration = duration / 1000;
    m_slider->setMaximum(m_duration);
}

void FrequencyPlayer::positionChanged(qint64 progress)
{
    if (!m_slider->isSliderDown())
        m_slider->setValue(progress / 1000);

    updateDurationInfo(progress / 1000);
}
#endif

#if 0
void FrequencyPlayer::metaDataChanged()
{
    if (m_player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2")
                .arg(m_player->metaData(QMediaMetaData::AlbumArtist).toString())
                .arg(m_player->metaData(QMediaMetaData::Title).toString()));

        if (m_coverLabel) {
            QUrl url = m_player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            m_coverLabel->setPixmap(!url.isEmpty()
                    ? QPixmap(url.toString())
                    : QPixmap());
        }
    }
}
#endif

void
FrequencyPlayer::jump(const int idx)
{
    m_playlist->setCurrentIndex(idx);
    m_player->play();
}

void
FrequencyPlayer::play(const int fid)
{
    jump(fid);
}

#if 0
void FrequencyPlayer::playlistPositionChanged(int currentItem)
{
    clearHistogram();
    m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
}
#endif

#if 0
void FrequencyPlayer::seek(int seconds)
{
    m_player->setPosition(seconds * 1000);
}
#endif

void FrequencyPlayer::statusChanged(QMediaPlayer::MediaStatus status)
{
#if 0
    handleCursor(status);
#endif

    // handle status message
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
        setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia:
        setStatusInfo(tr("Loading..."));
        break;
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
        setStatusInfo(tr("Buffering %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::StalledMedia:
        setStatusInfo(tr("Stalled %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::EndOfMedia:
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
        displayErrorMessage();
        break;
    }
}

void FrequencyPlayer::stateChanged(QMediaPlayer::State /* state */)
{
#if 0
    if (state == QMediaPlayer::StoppedState)
        clearHistogram();
#endif
}

#if 0
void FrequencyPlayer::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
        status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}
#endif

void FrequencyPlayer::bufferingProgress(int progress)
{
    QString msg;

    if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
        msg.append(tr("Stalled %1%")).arg(progress);
    else
        msg.append(tr("Buffering %1%")).arg(progress);

    setStatusInfo(msg);
    qDebug() << msg;
}

void FrequencyPlayer::setStatusInfo(const QString &info)
{
    qDebug() << info;
    setWindowTitle(info);
}

void FrequencyPlayer::displayErrorMessage()
{
    qDebug() << (m_player->errorString());
    setStatusInfo(m_player->errorString());
}
