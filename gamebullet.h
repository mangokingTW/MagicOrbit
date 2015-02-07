#ifndef GAMEBULLET_H
#define GAMEBULLET_H

#include "gameobject.h"

class GameBullet : public GameObject
{
public:
    GameBullet();
    ~GameBullet();
    void GameUpdate(qint64 delta);
};

#endif // GAMEBULLET_H
