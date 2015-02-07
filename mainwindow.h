#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include "gameview.h"
#include "gamescene.h"
#include "menubutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Start();
    void GameStart();
    void GameInit();
    void CleanScene();
    void LoadGameScene();
    void MenuScene();
    void QueryData();
    void TransferData();
    void SetParentApplication(QApplication *a);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    QPoint CursorPos;
    bool in_Menu;
    bool in_Game;

public slots:
    void StartSlot();
    void ExitSlot();
    void BackSlot();
    void GameOverSlot();

private:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    GameScene *scene;
    GameView *view;
    QApplication *a;
    void initWindow();
    //void GameLoop();
};

#endif // MAINWINDOW_H
