#include "gamescene.h"
#include "configure.h"
#include <QDebug>
#include <QTime>
#include <QThread>
#include <QDir>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

GameScene::GameScene()
{
    hero = new GameRole();
    MO = new GameMagicOrbit;
    ClockText = new QGraphicsTextItem;
    FPSText = new QGraphicsTextItem;
    camera = new GameCamera;
    GameRunning = false;
    Updating = false;
    MouseClick = 0;
}

GameScene::~GameScene()
{
}

void GameScene::GameStartInit()
{
    QFont font;
    font.setPixelSize(30);
    font.setBold(false);
    font.setFamily("Calibri");
    QColor color;
    color = Qt::white;
    ClockText->setPos(70,30);
    ClockText->setFont(font);
    ClockText->setPlainText(QTime::currentTime().toString());
    ClockText->setDefaultTextColor(color);
    this->addItem(ClockText);

    font.setPixelSize(20);
    FPSText->setPos(900,30);
    FPSText->setFont(font);
    FPSText->setPlainText("");
    FPSText->setDefaultTextColor(color);
    this->addItem(FPSText);

    hero->GameInit();
    this->addItem(hero);

    MO->GameInit();
    MO->TrackObject = hero;
    this->addItem(MO);

    GameGeoPlatform *pf1 =new GameGeoPlatform;
    this->addItem(pf1);
    this->platformList.push_back(pf1);

    GameHealthBar* HPbar = new GameHealthBar;
    HPbar->drawHPbar(100);
    this->hero->HPbar = HPbar;
    this->addItem(HPbar);

    GameMonsterSkeletonRider *mon = new GameMonsterSkeletonRider;
    mon->Init();
    mon->setPos(500,700);
    mon->ABSx = 500;mon->ABSy = 700-mon->pixmap().height();
    this->addItem(mon);
    this->addItem(mon->HPbar);
    this->monsterList.push_back(mon);

    this->camera->ABSx = 0;
    this->camera->ABSy = 0;
    MouseClick = 0;

    ItemPosUpdate(1);

    GameRunning = true;
}

void GameScene::GameUpdate(qint64 delta)
{
    this->ElementUpdate(delta);
    this->hero->GameUpdate(delta);
    this->MO->GameUpdate(delta);
    this->ObjectUpdate(delta);
    this->ItemPosUpdate(delta);
    this->ItemCollision();
    //this->RandomCreateMine(delta);
}

void GameScene::ElementUpdate(qint64 delta)
{
    MO->CursorPos = CursorPos;
}

void GameScene::ObjectUpdate(qint64 delta)
{
    foreach (GameBullet *bullet, this->bulletList ) {
        bullet->GameUpdate(delta);
    }
}

void GameScene::ItemPosUpdate(qint64 delta)
{
    if( this->hero->ABSx - this->camera->ABSx > 600 ) this->camera->ABSx = this->hero->ABSx - 600;
    if( this->hero->ABSx - this->camera->ABSx < 300 ) this->camera->ABSx = this->hero->ABSx - 300;
    this->hero->setPos(this->hero->ABSx - this->camera->ABSx - this->hero->pixmap().width()/2 ,this->hero->ABSy - this->camera->ABSy - this->hero->pixmap().height());
    this->MO->setPos(MO->ABSx-camera->ABSx,MO->ABSy-camera->ABSy);

    foreach (GameGeoPlatform *pf, this->platformList) {
        pf->setPos( pf->ABSx - this->camera->ABSx , pf->ABSy - this->camera->ABSy );
    }
    foreach (GameMineObject *mine, this->mineList ) {
        mine->setPos( mine->ABSx - this->camera->ABSx , mine->ABSy - this->camera->ABSy - mine->pixmap().height() );
    }
    foreach (GameBullet *bullet, this->bulletList ) {
        bullet->setPos( bullet->ABSx - this->camera->ABSx , bullet->ABSy - this->camera->ABSy );
        if( bullet->ABSx - hero->ABSx > 1000 || bullet->ABSx - hero->ABSx < -1000 )
        {
            this->bulletList.removeAll(bullet);
            this->removeItem(bullet);
            delete bullet;
        }
    }
    foreach (GameMonster *mon, this->monsterList ) {
        mon->GameUpdate(delta,this->camera->ABSx,this->camera->ABSy);
    }
}

void GameScene::ItemCollision()
{
    foreach (GameGeoPlatform *pf, this->platformList) {
        if( hero->Prex < pf->ABSx+pf->width && pf->ABSx < hero->ABSx && hero->Prey <= pf->ABSy && hero->ABSy >= pf->ABSy )
        {
            hero->ABSy = pf->ABSy;
            hero->iyVer = 0;
        }
    }

    foreach (GameMineObject *mine, this->mineList ) {
        if(mine->collidesWithItem(this->hero))
        {
            this->hero->HP -= 20;
            if( this->hero->HP > 0 )
                this->hero->HPbar->drawHPbar(this->hero->HP);
            else
            {
                this->hero->HPbar->drawHPbar(0);
                GameRunning = false;
                break;
            }
            this->mineList.removeAll(mine);
            this->removeItem(mine);
            delete mine;
        }
    }

    foreach (GameMonster *mon, this->monsterList ) {
        foreach (GameBullet *bullet, this->bulletList ) {
            if(bullet->collidesWithItem(mon))
            {
                mon->inject(10);
                this->bulletList.removeAll(bullet);
                this->removeItem(bullet);
                delete bullet;
                break;
            }
        }

        if( mon->collidesWithItem(MO))
        {
            mon->inject(10);
        }

        if( mon->HP <= 0 )
        {
            this->removeItem(mon->HPbar);
            this->removeItem(mon);
            this->monsterList.removeAll(mon);
            delete mon;
        }
    }
}

void GameScene::CreateBullet()
{
    GameBullet *bullet = new GameBullet();
    bullet->setPixmap(QPixmap( Config::FilePreix + "bullet.png"));
    QPoint vector = CursorPos - QPoint(hero->x()+hero->pixmap().width()/2,hero->y()+hero->pixmap().height()/2 );
    qint32 distant = vector.manhattanLength();
    bullet->ixVer = 200 * vector.x() / distant;
    bullet->iyVer = 200 * vector.y() / distant;
    bullet->ABSx = this->hero->ABSx;
    bullet->ABSy = this->hero->ABSy - this->hero->pixmap().height()/2;
    bullet->setPos( bullet->ABSx - this->camera->ABSx , bullet->ABSy - this->camera->ABSy );
    this->addItem(bullet);
    this->bulletList.push_back(bullet);
}

void GameScene::RandomCreateMine(qint64 delta)
{
    if( qrand()% (1000*delta/100+5000) > 5000 )
    {
        if( this->mineList.isEmpty()  || this->mineList.last()->ABSx - this->hero->ABSx < 700 )
        {
        GameMineObject *mine = new GameMineObject();
        mine->setPixmap(QPixmap( Config::FilePreix + "mine.png"));
        mine->ABSx = this->hero->ABSx+1000;
        mine->ABSy = 700;
        mine->setPos( mine->ABSx - this->camera->ABSx , mine->ABSy - this->camera->ABSy - mine->pixmap().height() );
        this->addItem(mine);
        this->mineList.push_back(mine);
        }
    }
}

void GameScene::CleanScene()
{
    foreach (QGraphicsItem *p, this->items()) {
        this->removeItem(p);
    }
    foreach (GameMineObject *mine, this->mineList ) {
        delete mine;
    }
    foreach (GameBullet *bullet, this->bulletList ) {
        delete bullet;
    }
    this->mineList.clear();
    this->bulletList.clear();
    this->clear();
}

QGraphicsView * GameScene::GetView()
{
    return this->view;
}

void GameScene::keyPressEvent ( QKeyEvent * event )
{
    qDebug()<< "Press : "<< event->key();
    switch (event->key()) {
    case Qt::Key_D:
    case Qt::Key_Right:
        this->hero->RightRelease = false;this->hero->RightKey = true;this->hero->RightKeyPress = true;
        event->accept();
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        this->hero->LeftRelease = false;this->hero->LeftKey = true;this->hero->LeftKeyPress = true;
        event->accept();
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        this->hero->UpRelease = false;this->hero->UpKey = true;this->hero->UpKeyPress = true;
        event->accept();
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        this->hero->DownRelease = false;this->hero->DownKey = true;this->hero->DownKeyPress = true;
        event->accept();
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        break;
    }
}

void GameScene::keyReleaseEvent ( QKeyEvent * event )
{
    qDebug()<< "Release : "<< event->key();
    switch (event->key()) {
    case Qt::Key_D:
    case Qt::Key_Right:
        this->hero->RightRelease = true;
        event->accept();
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        this->hero->LeftRelease = true;
        event->accept();
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        this->hero->UpRelease = true;
        event->accept();
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        this->hero->DownRelease = true;
        event->accept();
        break;
    default:
        QGraphicsScene::keyReleaseEvent(event);
        break;
    }
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::RightButton:
        break;
    case Qt::LeftButton:
        //event->accept();
        break;
    }
    QGraphicsScene::mousePressEvent(event);
    event->accept();

}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::RightButton:
        break;
    case Qt::LeftButton:
        this->MO->Clicked = true;
        QGraphicsScene::mouseReleaseEvent(event);
        event->accept();
        break;
    }

}
