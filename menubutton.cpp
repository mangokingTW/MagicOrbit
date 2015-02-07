#include "mainwindow.h"
#include "menubutton.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QThread>

MenuButton::MenuButton()
{
    this->ButtonType = ButtonType::InvalidType;
}

MenuButton::MenuButton(QPixmap pix)
{
    this->setPixmap(pix);
}

MenuButton::~MenuButton()
{

}

void MenuButton::setButtonType(const qint32 T)
{
    this->ButtonType = T;
}

void MenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Press start button" ;
    QGraphicsItem::mousePressEvent(event);
    event->accept();
}

void MenuButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Release button";
   // event->accept();
    switch(this->ButtonType)
    {
    case ButtonType::StartType :
        qDebug() << "Game start";
        this->StartPressed();
        break;
    case ButtonType::ExitType :
        qDebug() << "Closing Game";
        this->ExitPressed();
        break;
    case ButtonType::BackType :
        qDebug() << "Back Menu";
        this->BackPressed();
        break;
    default :
        qDebug() << "Unknown Button" << this->ButtonType;
        break;
    }

    QGraphicsItem::mousePressEvent(event);
    event->accept();
}
