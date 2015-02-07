#include "gamemagicorbit.h"

GameMagicOrbit::GameMagicOrbit()
{

}

GameMagicOrbit::~GameMagicOrbit()
{

}

void GameMagicOrbit::GameInit()
{
    setPixmap(Config::FilePreix + "bullet.png");
    setPos(300,700);
    ABSx = 300;
    ABSy = 700;
    Clicked = false;
}

void GameMagicOrbit::GameUpdate(qint64 delta)
{
    Prex = ABSx;
    Prey = ABSy;
    qreal ratio = qreal(delta)/100;
    Shooting(delta);
    Tracking(delta);
    //iyAcc += 1;
    ixVer *= 0.8;
    iyVer *= 0.8;
    ABSx += ixVer * ratio;
    ABSy += iyVer * ratio;
    ixAcc *= 0.5;
    iyAcc *= 0.5;
}

void GameMagicOrbit::Shooting(qint64 delta)
{
    if(Clicked)
    {
        QPointF vector = CursorPos - QPointF(this->x(),this->y());
        qreal distant = vector.manhattanLength();
        if( distant > 100 )
        {
            ixAcc += 20 * vector.x()/distant*sqrt(distant);
            iyAcc += 20 * vector.y()/distant*sqrt(distant);
        }
        Clicked = false;
        ixVer += ixAcc;
        iyVer += iyAcc;
    }
}

void GameMagicOrbit::Tracking(qint64 delta)
{
    //qreal ratio = qreal(delta)/100;
    //QPointF TrackCenter = QPoint(TrackObject->ABSx - TrackObject->pixmap().width()/2 , TrackObject->ABSy - TrackObject->pixmap().height()/2);
    QPointF TrackCenter = QPointF(TrackObject->ABSx, TrackObject->ABSy - TrackObject->pixmap().height()/2);
    QPointF vector = TrackCenter - QPoint(this->ABSx,this->ABSy);
    qreal distant = vector.manhattanLength();

    if( distant > 10 )
    {
        ixAcc += 1*vector.x()/distant*sqrt(distant);//*qAbs(vector.x()/distant);
        iyAcc += 1*vector.y()/distant*sqrt(distant);//*qAbs(vector.y()/distant);
    }
    else
    {
        ixAcc = 0;
        iyAcc = 0;
    }
    ixVer += ixAcc;
    iyVer += iyAcc;
}
