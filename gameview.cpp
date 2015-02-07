#include "gameview.h"
#include <QKeyEvent>
#include <QDebug>

GameView::GameView()
{
}

GameView::~GameView()
{

}

void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsView::keyReleaseEvent(event);
}

