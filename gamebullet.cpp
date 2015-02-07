#include "gamebullet.h"

GameBullet::GameBullet()
{
}

GameBullet::~GameBullet()
{

}

void GameBullet::GameUpdate(qint64 delta)
{
    qreal ratio = qreal(delta)/100;
    ixVer += ixAcc * ratio;
    iyVer += iyAcc * ratio;
    this->ABSx = this->ABSx + ixVer* ratio;
    this->ABSy = this->ABSy + iyVer* ratio;
}
