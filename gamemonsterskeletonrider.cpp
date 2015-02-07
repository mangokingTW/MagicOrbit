#include "gamemonsterskeletonrider.h"
#include <QColor>
#include <QGraphicsScene>
#include <QPainter>


GameMonsterSkeletonRider::GameMonsterSkeletonRider()
{
    this->HPbar = new QGraphicsPixmapItem;
}

GameMonsterSkeletonRider::~GameMonsterSkeletonRider()
{
    delete HPbar;
}

void GameMonsterSkeletonRider::Init()
{
    this->Type = QString("skeleton");
    this->Name = QString("Skeleton Rider");
    this->setPixmap(QPixmap(Config::FilePreix+"skeleton_rider.png").scaledToHeight(300));
    this->FullHP = 1000;
    this->HP = 1000;
    HPbarInit();
}

void GameMonsterSkeletonRider::HPbarInit()
{
    QPixmap pix(this->pixmap().width(),20);
    pix.fill(Qt::black);
    QPainter paint(&pix);
    paint.setBrush(QColor(255,34,34,255));
    paint.drawRect(0,0,this->pixmap().width(),20);
    this->HPbar->setPixmap(pix);
}

void GameMonsterSkeletonRider::inject(qreal damage)
{
    this->HP -= damage;
    QPixmap pix(this->pixmap().width(),20);
    pix.fill(Qt::black);
    QPainter paint(&pix);
    paint.setBrush(QColor(255,34,34,255));
    paint.drawRect(0,0,(1-((FullHP-HP)/FullHP))*this->pixmap().width(),20);
    this->HPbar->setPixmap(pix);
}

void GameMonsterSkeletonRider::GameUpdate(qint64 delta, qreal cameraX, qreal cameraY)
{
    this->ABSx += 1;
    this->setPos(this->ABSx-cameraX,this->ABSy-cameraY );
    this->HPbar->setPos(this->ABSx-cameraX,this->ABSy-cameraY-40);
    //QImage a = QImage(Config::FilePreix+"skeleton_rider.png").convertToFormat(QImage::Format_RGBA8888);
    /*
    static qint32 i = 0;
    if(i++%100<50)
    {
        for( int x = 0 ; x < a.width() ; x++ )
        {
            for( int y = 0 ; y < a.height() ; y++ )
            {
                QRgb c = a.pixel(x,y);
                c = c|0x00FF0000;
                a.setPixel(x,y,c);
            }
        }
    }
    else
    {
        for( int x = 0 ; x < a.width() ; x++ )
        {
            for( int y = 0 ; y < a.height() ; y++ )
            {
                QRgb c = a.pixel(x,y);
                c = c&0xFF00FFFF;
                a.setPixel(x,y,c);
            }
        }
    }
    QPixmap b = QPixmap::fromImage(a).scaledToHeight(300);
    this->setPixmap(b);
    */
}
