#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.SetParentApplication(&a);
    w.show();
    w.Start();
    a.exit();
    return 0;
}
