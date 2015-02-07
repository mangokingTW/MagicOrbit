#include "mainwindow.h"
#include "menubutton.h"
#include "configure.h"
#include <QDebug>
#include <QThread>
#include <QElapsedTimer>
#include <QTime>
#include <QCloseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initWindow()
{
    this->setFixedSize(1600,900);

    this->scene = new GameScene;
    this->scene->setParent(this);
    this->scene->setSceneRect(0,0,1600,900);

    this->view = new GameView;
    this->view->setFixedSize(1600,900);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    this->view->setBackgroundBrush(QPixmap(Config::FilePreix + "BG.jpg").scaledToHeight(900 , Qt::FastTransformation));
    this->view->setScene(this->scene);

    in_Menu = false;
    in_Game = false;

}

void MainWindow::Start()
{
    this->in_Menu = true;
    while(this->in_Menu)MenuScene();
}

void MainWindow::MenuScene()
{
    qDebug() << "Menu open...";
    MenuButton *startbutton = new MenuButton(QPixmap(Config::FilePreix + "start.png"));
    startbutton->setPos(650,400);
    startbutton->setButtonType(ButtonType::StartType);
    this->scene->addItem(startbutton);

    MenuButton *exitbutton = new MenuButton(QPixmap(Config::FilePreix + "exit.png"));
    exitbutton->setPos(650,550);
    exitbutton->setButtonType(ButtonType::ExitType);
    this->scene->addItem(exitbutton);

    this->setCentralWidget(this->view);
    connect(startbutton,SIGNAL(StartPressed()),this,SLOT(StartSlot()));
    connect(exitbutton,SIGNAL(ExitPressed()),this,SLOT(ExitSlot()));

    while( in_Menu && !in_Game )
        this->a->processEvents();

    qDebug() << "Exit Menu" ;
    disconnect(startbutton,SIGNAL(StartPressed()),this,SLOT(StartSlot()));
    disconnect(exitbutton,SIGNAL(ExitPressed()),this,SLOT(ExitSlot()));

    if( in_Game )
    {
        GameStart();
    }

    delete startbutton;
    delete exitbutton;

}

void MainWindow::GameStart()
{
    qDebug() << "Gaming";
    GameInit();
    QElapsedTimer timer;
    qint64 delta;
    timer.start();
    while( this->scene->GameRunning )
    {
        delta = timer.nsecsElapsed()/1000000;
        this->a->processEvents();
        if( delta < 16  ) continue;
        timer.restart();
        this->QueryData();
        this->TransferData();
        this->scene->GameUpdate(delta);
        this->scene->ClockText->setPlainText(QTime::currentTime().toString());
        this->scene->FPSText->setPlainText("FPS : " + QString::number(1000/delta));
        this->view->update();
    }
    qDebug()<<"Game Over... Clean scene.";
    CleanScene();
    qDebug()<<"Clean up.";
}

void MainWindow::QueryData()
{
    this->CursorPos = this->mapFromGlobal(QCursor::pos());
}

void MainWindow::TransferData()
{
    this->scene->CursorPos = this->CursorPos;
}

void MainWindow::GameInit()
{
    CleanScene();
    LoadGameScene();
    this->scene->GameStartInit();
}

void MainWindow::LoadGameScene()
{
    MenuButton *backbutton = new MenuButton(QPixmap(Config::FilePreix +"back.png"));
    backbutton->setPos(1300,800);
    backbutton->setButtonType(ButtonType::BackType);
    this->scene->addItem(backbutton);

    connect(backbutton,SIGNAL(BackPressed()),this,SLOT(BackSlot()));
}

void MainWindow::CleanScene()
{
    this->scene->CleanScene();
}

void MainWindow::StartSlot()
{
    in_Game = true;
    in_Menu = true;
}

void MainWindow::ExitSlot()
{
    in_Menu = false;
    in_Game = false;
    scene->GameRunning = false;
    this->a->exit();
}

void MainWindow::BackSlot()
{
    in_Game = false;
    in_Menu = true;
    scene->GameRunning = false;
}

void MainWindow::GameOverSlot()
{
    in_Game = false;
    in_Menu = true;
    scene->GameRunning = false;
}

void MainWindow::SetParentApplication(QApplication *a )
{
    this->a = a;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMainWindow::mouseReleaseEvent(event);
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    event->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<"Enter Release";
    switch(event->key())
    {
    case Qt::Key_Enter :
    case Qt::Key_Space :
    case Qt::Key_Return :
            qDebug()<<"Enter Press";
            StartSlot();
            event->accept();
            break;
    case Qt::Key_Backspace:
            BackSlot();
            event->accept();
            break;
    case Qt::Key_Escape :
            qDebug()<<"Exit Press";
            ExitSlot();
            event->accept();
            break;
    default:
            break;
    }
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->in_Menu = false;
    this->in_Game = false;
    this->scene->GameRunning = false;
    qDebug() << "Closing Window...";
    QMainWindow::closeEvent(event);
    event->accept();
}
