/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
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
    controls->setState(m_player->state());
    controls->setVolume(m_player->volume());
    controls->setMuted(controls->isMuted());

    connect(controls, &FrequencyPlayerControls::play, m_player, &QMediaPlayer::play);
    connect(controls, &FrequencyPlayerControls::stop, m_player, &QMediaPlayer::stop);
#if 0
    connect(controls, &FrequencyPlayerControls::pause, m_player, &QMediaPlayer::pause);
    connect(controls, &FrequencyPlayerControls::next, m_playlist, &QMediaPlaylist::next);
    connect(controls, &FrequencyPlayerControls::previous, this, &FrequencyPlayer::previousClicked);
#endif
    connect(controls, &FrequencyPlayerControls::changeVolume, m_player, &QMediaPlayer::setVolume);
    connect(controls, &FrequencyPlayerControls::changeMuting, m_player, &QMediaPlayer::setMuted);
#if 0
    connect(controls, &FrequencyPlayerControls::changeRate, m_player, &QMediaPlayer::setPlaybackRate);
#endif

    connect(m_player, &QMediaPlayer::stateChanged, controls, &FrequencyPlayerControls::setState);
    connect(m_player, &QMediaPlayer::volumeChanged, controls, &FrequencyPlayerControls::setVolume);
    connect(m_player, &QMediaPlayer::mutedChanged, controls, &FrequencyPlayerControls::setMuted);

#if 0
    m_fullScreenButton = new QPushButton(tr("FullScreen"), this);
    m_fullScreenButton->setCheckable(true);

    m_colorButton = new QPushButton(tr("Color Options..."), this);
    m_colorButton->setEnabled(false);
    connect(m_colorButton, &QPushButton::clicked, this, &FrequencyPlayer::showColorDialog);
#endif

#if 0
    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(m_playlistView);
#endif

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
#if 0
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
#endif
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
#if 0
    controlLayout->addWidget(m_fullScreenButton);
    controlLayout->addWidget(m_colorButton);
#endif

#if 0
    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(displayLayout);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_slider);
    hLayout->addWidget(m_labelDuration);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);
    layout->addLayout(histogramLayout);
#endif
#if defined(Q_OS_QNX)
    // On QNX, the main window doesn't have a title bar (or any other decorations).
    // Create a status bar for the status information instead.
    m_statusLabel = new QLabel;
    m_statusBar = new QStatusBar;
    m_statusBar->addPermanentWidget(m_statusLabel);
    m_statusBar->setSizeGripEnabled(false); // Without mouse grabbing, it doesn't work very well.
    layout->addWidget(m_statusBar);
#endif

    setLayout(controlLayout);

    if (!isPlayerAvailable()) {
        QMessageBox::warning(this, tr("Service not available"),
                             tr("The QMediaPlayer object does not have a valid service.\n"\
                                "Please check the media service plugins are installed."));

        controls->setEnabled(false);
#if 0
        m_playlistView->setEnabled(false);
        openButton->setEnabled(false);
        m_colorButton->setEnabled(false);
        m_fullScreenButton->setEnabled(false);
#endif
    }

#if 0
    metaDataChanged();
#endif
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

void FrequencyPlayer::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if (m_player->position() <= 5000)
        m_playlist->previous();
    else
        m_player->setPosition(0);
}

void FrequencyPlayer::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        m_playlist->setCurrentIndex(index.row());
        m_player->play();
    }
}

#if 0
void FrequencyPlayer::playlistPositionChanged(int currentItem)
{
    clearHistogram();
    m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
}
#endif

void FrequencyPlayer::seek(int seconds)
{
    m_player->setPosition(seconds * 1000);
}

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
    if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
        setStatusInfo(tr("Stalled %1%").arg(progress));
    else
        setStatusInfo(tr("Buffering %1%").arg(progress));
}

#if 0
void FrequencyPlayer::setTrackInfo(const QString &info)
{
    m_trackInfo = info;

    if (m_statusBar) {
        m_statusBar->showMessage(m_trackInfo);
        m_statusLabel->setText(m_statusInfo);
    } else {
        if (!m_statusInfo.isEmpty())
            setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
        else
            setWindowTitle(m_trackInfo);
    }
}
#endif

void FrequencyPlayer::setStatusInfo(const QString &info)
{
#if 0
    m_statusInfo = info;

    if (m_statusBar) {
        m_statusBar->showMessage(m_trackInfo);
        m_statusLabel->setText(m_statusInfo);
    } else {
        if (!m_statusInfo.isEmpty())
            setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
        else
            setWindowTitle(m_trackInfo);
    }
#endif
    setWindowTitle(info);
}

void FrequencyPlayer::displayErrorMessage()
{
    qDebug() << (m_player->errorString());
    setStatusInfo(m_player->errorString());
}

#if 0
void FrequencyPlayer::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || m_duration) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
            m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    m_labelDuration->setText(tStr);
}
#endif

#if 0
void FrequencyPlayer::clearHistogram()
{
    QMetaObject::invokeMethod(m_videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
    QMetaObject::invokeMethod(m_audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
}
#endif
