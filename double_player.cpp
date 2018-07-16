
#include "double_player.h"

DoublePlayer::DoublePlayer(QWidget *parent)
    : QGroupBox("v4m", parent)
{
//! [create-objs]
    m_player[0] = new Player(this);
    m_player[1] = new Player(this);
//! [create-objs]

    layout.addWidget(m_player[0]);
    layout.addWidget(m_player[1]);
    layout.addStretch(1);
    this->setLayout(&layout);
}

DoublePlayer::~DoublePlayer()
{
}

Player& DoublePlayer::player(qint64 idx)
{
    return *m_player[idx];
}
