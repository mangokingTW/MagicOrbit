#ifndef GAMEMONSTER_H
#define GAMEMONSTER_H

#include "gameobject.h"
#include "configure.h"

class GameMonster : public GameObject
{
public:
    GameMonster();
    ~GameMonster();
    virtual void Init();
    virtual void inject(qreal damage);
    virtual void GameUpdate(qint64 delta, qreal cameraX, qreal cameraY);
    QGraphicsPixmapItem *HPbar;
    QString Type;
    QString Name;
    qreal FullHP;
    qreal FullMP;
    qreal HP;
    qreal MP;
};

#endif // GAMEMONSTER_H
