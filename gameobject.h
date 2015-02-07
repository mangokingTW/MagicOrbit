#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>

class GameObject : public QGraphicsPixmapItem
{
public:
    GameObject();
    ~GameObject();
    qint32 height;
    qint32 width;
    qreal ixVer;
    qreal iyVer;
    qreal ixAcc;
    qreal iyAcc;
    qreal ABSx;
    qreal ABSy;
    qreal Prex;
    qreal Prey;
};

#endif // GAMEOBJECT_H
