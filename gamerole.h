#ifndef GAMEROLE_H
#define GAMEROLE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "gameobject.h"
#include "gamehealthbar.h"

#define stand_status 0
#define walk_status 1
#define jump_status 2

#define null_sprite -1
#define stand_sprite 0
#define walk_sprite 1
#define walk2_sprite 2
#define walk3_sprite 3
#define jump_sprite 4

class GameRole : public GameObject , public QObject
{
public:
    GameRole();
    ~GameRole();
    void GameInit();
    void GameUpdate(qint64 delta);
    void MotionUpdate(qint64 delta);
    void SpriteChange(qint32 status);
    void InputDealer();
    bool RightKey;
    bool LeftKey;
    bool UpKey;
    bool DownKey;
    bool RightRelease;
    bool LeftRelease;
    bool UpRelease;
    bool DownRelease;
    bool RightKeyPress;
    bool LeftKeyPress;
    bool UpKeyPress;
    bool DownKeyPress;
    bool PixmapReflect;
    qreal HP;
    qint32 status;
    qint32 last_status;
    qint32 sprite_id;
    qint64 motion_time_counter;
    QPixmap sprite;
    QPixmap sprite_stand;
    QPixmap sprite_walk;
    QPixmap sprite_walk2;
    QPixmap sprite_walk3;
    QPixmap sprite_jump;
    GameHealthBar *HPbar;
};

#endif // GAMEROLE_H
