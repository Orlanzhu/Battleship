#include "mainwindow.h"
#include "gamewindow.h"
#include "gameboard.hpp"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //+++++++Center the mainWindow+++++
    int W = 500;
    int H = 420;
    int screenWidth;
    int screenHeight;
    int x, y;

    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->width();
    screenHeight = desktop->height();
    x = (screenWidth - W) / 2;
    y = (screenHeight - H) / 2;
    w.resize(W, H);
    w.move(x,y);
    //++++++++++++++++++++++++++++++++
    w.show();
    return a.exec();
}
