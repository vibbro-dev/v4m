
#ifndef DOUBLE_PLAYER_H
#define DOUBLE_PLAYER_H

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

#endif // DOUBLE_PLAYER_H

