#ifndef GAMEHEALTHBAR_H
#define GAMEHEALTHBAR_H

#include <QGraphicsPixmapItem>

class GameHealthBar: public QGraphicsPixmapItem
{
public:
    GameHealthBar();
    ~GameHealthBar();
    void GameUpdate(qint64 delta);
    void drawHPbar(qreal HP);
};

#endif // GAMEHEALTHBAR_H
