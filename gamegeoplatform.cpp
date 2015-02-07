#include "gamegeoplatform.h"
#include <QPainter>

GameGeoPlatform::GameGeoPlatform()
{
    ABSx = 200;
    ABSy = 500;
    width = 500;
    QPixmap pix(500,50);
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    paint.setBrush(QColor(255,200,100,255));
    paint.drawRect(0,0,499,49);
    this->setPixmap(pix);
    this->setPos(200,600);
}

GameGeoPlatform::~GameGeoPlatform()
{

}

