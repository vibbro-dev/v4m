/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc
** License GNU GPL 3
**
****************************************************************************/

#if !defined(_V4M_FREQUENCY_PLAYER_CONTROLS_H_)
#define _V4M_FREQUENCY_PLAYER_CONTROLS_H_

#include <QMediaPlayer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class FrequencyPlayerControls : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyPlayerControls(QWidget *parent = nullptr);

    QMediaPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
#if 0
    qreal playbackRate() const;
#endif

public slots:
    void setState(QMediaPlayer::State state);
    void setVolume(int volume);
    void setMuted(bool muted);
#if 0
    void setPlaybackRate(float rate);
#endif

signals:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void changeVolume(int volume);
    void changeMuting(bool muting);
#if 0
    void changeRate(qreal rate);
#endif

private slots:
    void playClicked();
    void muteClicked();
#if 0
    void updateRate();
#endif
    void onVolumeSliderValueChanged();

private:
    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
    bool m_playerMuted = false;
    QAbstractButton *m_playButton = nullptr;
    QAbstractButton *m_stopButton = nullptr;
    QAbstractButton *m_nextButton = nullptr;
    QAbstractButton *m_previousButton = nullptr;
    QAbstractButton *m_muteButton = nullptr;
    QAbstractSlider *m_volumeSlider = nullptr;
#if 0
    QComboBox *m_rateBox = nullptr;
#endif
};

#endif // _V4M_FREQUENCY_PLAYER_CONTROLS_H_
