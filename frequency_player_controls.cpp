/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc
**
** Licensed GNU GPL 3
**
****************************************************************************/

#include "frequency_player_controls.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QAudio>

static const QStringList frequencyColors { "blue", "yellow", "green", "orange", "red", "fuchsia", "brown", "cyan" };

FrequencyPlayerControls::FrequencyPlayerControls(QWidget *parent)
    : QWidget(parent)
{
    m_frequencySelector = new QButtonGroup(this);
    for (int k = 0; k < numberOfFrequencies(); ++k)
        m_frequencySelector->addButton(new QRadioButton(frequencyColors[k], this), k);

    connect(m_frequencySelector, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &FrequencyPlayerControls::frequencySelectorClicked);

    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setEnabled(false);

    connect(m_stopButton, &QAbstractButton::clicked, this, &FrequencyPlayerControls::stop);

    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);

    connect(m_volumeSlider, &QSlider::valueChanged, this, &FrequencyPlayerControls::onVolumeSliderValueChanged);

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    // layout->addWidget(m_frequencySelector);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_volumeSlider);
}

QMediaPlayer::State
FrequencyPlayerControls::state() const
{
    return m_playerState;
}

void
FrequencyPlayerControls::setState(QMediaPlayer::State state)
{
    if (state != m_playerState) {
        m_playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            m_stopButton->setEnabled(false);
        case QMediaPlayer::PlayingState:
            m_stopButton->setEnabled(true);
            break;
        }
    }
}

void
FrequencyPlayerControls::setVolume(int volume)
{
    qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100),
                                                    QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    m_volumeSlider->setValue(qRound(logarithmicVolume * 100));
}

void
FrequencyPlayerControls::frequencySelectorClicked(int fid)
{
    m_playerState = QMediaPlayer::PlayingState;
    emit play(fid);
}


void
FrequencyPlayerControls::stopClicked()
{
    m_playerState = QMediaPlayer::StoppedState;
    emit stop();
}

void
FrequencyPlayerControls::onVolumeSliderValueChanged()
{
    emit changeVolume(volume());
}

int
FrequencyPlayerControls::volume() const
{
    qreal linearVolume =  QAudio::convertVolume(m_volumeSlider->value() / qreal(100),
                                                QAudio::LogarithmicVolumeScale,
                                                QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
}
