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

#include "double_player.h"

DoublePlayer::DoublePlayer(QWidget *parent)
    : QGroupBox("v4m", parent)
{
//! [create-objs]
    m_player = new Player(this);
    m_fplayer = new FrequencyPlayer(this);
//! [create-objs]

    layout.addWidget(m_player);
    layout.addWidget(m_fplayer);
    layout.addStretch(1);
    this->setLayout(&layout);
}

DoublePlayer::~DoublePlayer()
{
}

Player& DoublePlayer::player()
{
    return *m_player;
}

FrequencyPlayer& DoublePlayer::frequencyPlayer()
{
    return *m_fplayer;
}
