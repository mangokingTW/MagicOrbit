#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QGraphicsPixmapItem>
#include <QObject>

namespace ButtonType {
const qint32 InvalidType { 0 };
const qint32 StartType { 1 };
const qint32 ExitType { 2 };
const qint32 BackType { 3 };
}


class MenuButton : public QObject ,  public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    MenuButton();
    MenuButton(QPixmap pix);
    ~MenuButton();
    void setButtonType(const qint32 T);

public slots:

signals:
    void ExitPressed();
    void StartPressed();
    void BackPressed();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qint32 ButtonType;
};

#endif // MENUBUTTON_H
