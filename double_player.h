/****************************************************************************
**
** Copyright (C) 2018 Vibbro Snc.
**
** This small app is just to test the file location capabilities within Qt
** The target is to be able to locate all music files within a given device
**
** LICENSE: GNU GPL 3.0
**
****************************************************************************/

#ifndef _V4M_DOUBLE_PLAYER_H_
#define _V4M_DOUBLE_PLAYER_H_

#include <QGroupBox>
#include <QVBoxLayout>

#include "player.h"

class DoublePlayer : public QGroupBox
{
    Q_OBJECT

public:
    explicit DoublePlayer(QWidget *parent = nullptr);
    ~DoublePlayer();

    Player &player(qint64 idx);

signals:
    void fullScreenChanged(bool fullScreen);

private:
    Player *m_player[2] = { nullptr, nullptr };
    QVBoxLayout layout;
};

#endif // _V4M_DOUBLE_PLAYER_H_

