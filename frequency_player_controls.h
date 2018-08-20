/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc
** License GNU GPL 3
**
****************************************************************************/

#if !defined(_V4M_FREQUENCY_PLAYER_CONTROLS_H_)
#define _V4M_FREQUENCY_PLAYER_CONTROLS_H_

#include <QWidget>
#include <QMediaPlayer>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
class QWidget;
class QAbstractSlider;
class QAbstractButton;
QT_END_NAMESPACE

#define NUM_OF_FREQUENCIES   (2)

class FrequencyPlayerControls : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyPlayerControls(QWidget *parent = nullptr);

    int numberOfFrequencies() const { return (int) NUM_OF_FREQUENCIES; }
    int frequencyId() const         { return m_frequencySelector->checkedId(); }
    int volume() const;
    QMediaPlayer::State state() const;

public slots:
    void setVolume(int volume);
    void setState(QMediaPlayer::State state);

signals:
    void play(int fid);
    void stop();
    void changeVolume(int volume);


private:

    QButtonGroup *m_frequencySelector = nullptr;
    QAbstractButton *m_stopButton = nullptr;
    QAbstractSlider *m_volumeSlider = nullptr;

    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;

private slots:

    void frequencySelectorClicked(int);
    void stopClicked();
    void onVolumeSliderValueChanged();
};

#endif // _V4M_FREQUENCY_PLAYER_CONTROLS_H_
