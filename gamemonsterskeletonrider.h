#ifndef GAMEMONSTERSKELETONRIDER_H
#define GAMEMONSTERSKELETONRIDER_H

#include "gamemonster.h"

class GameMonsterSkeletonRider : public GameMonster
{
public:
    GameMonsterSkeletonRider();
    ~GameMonsterSkeletonRider();
    virtual void Init();
    virtual void inject(qreal damage);
    virtual void GameUpdate(qint64 delta, qreal cameraX, qreal cameraY);
    void HPbarInit();
};

#endif // GAMEMONSTERSKELETONRIDER_H
