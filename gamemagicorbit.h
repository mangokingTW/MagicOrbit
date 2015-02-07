#ifndef GAMEMAGICORBIT_H
#define GAMEMAGICORBIT_H

#include "configure.h"
#include "gameobject.h"
#include "gamerole.h"

class GameMagicOrbit : public GameObject
{
public:
    GameMagicOrbit();
    ~GameMagicOrbit();
    void GameInit();
    void GameUpdate(qint64 delta);
    void Shooting(qint64 delta);
    void Tracking(qint64 delta);
    GameObject *TrackObject;
    QPoint CursorPos;
    bool Clicked;
};

#endif // GAMEMAGICORBIT_H
