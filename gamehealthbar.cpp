#include "gamehealthbar.h"
#include <QPainter>

GameHealthBar::GameHealthBar()
{

}

GameHealthBar::~GameHealthBar()
{

}

void GameHealthBar::drawHPbar(qreal HP)
{
    QPixmap pix(50,500);
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    paint.setBrush(QColor(255,34,34,255));
    paint.drawRect(0,500-HP*5,49,HP*5-1);
    this->setPixmap(pix);
    this->setPos(20,40);
}
