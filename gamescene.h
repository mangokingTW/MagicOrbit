#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include "gamerole.h"
#include "gamecamera.h"
#include "gamemineobject.h"
#include "gamebullet.h"
#include "gamehealthbar.h"
#include "gamemonster.h"
#include "gamemonsterskeletonrider.h"
#include "gamemagicorbit.h"
#include "gamegeoplatform.h"

class GameScene : public QGraphicsScene
{

public:
    GameScene();
    ~GameScene();
    QGraphicsView *GetView();
    void GameStartInit();
    void GameUpdate(qint64 delta);
    void ElementUpdate(qint64 delta);
    void ObjectUpdate(qint64 delta);
    void ItemPosUpdate(qint64 delta);
    void ItemCollision();
    void CreateBullet();
    void RandomCreateMine(qint64 delta);
    void CleanScene();
    GameRole *hero;
    GameMagicOrbit *MO;
    GameCamera *camera;
    QGraphicsTextItem *ClockText;
    QGraphicsTextItem *FPSText;
    QPoint CursorPos;
    bool GameRunning;

signals:
    void GameOver();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    bool Updating;
    qint32 MouseClick;
    QList <GameMineObject *> mineList;
    QList <GameBullet *> bulletList;
    QList <GameMonster *> monsterList;
    QList <GameGeoPlatform *> platformList;
    QGraphicsView *view;
    QApplication *a;
};

#endif // GAMESCENE_H
