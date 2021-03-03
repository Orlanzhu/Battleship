#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameWindow=new GameWindow(this);
    connect(gameWindow,SIGNAL(endGame()),this,SLOT(ButtonEnd_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    hide();
    gameWindow->show();
    gameWindow->gameMode=0;
}

void MainWindow::on_pushButton_2_clicked()
{
    hide();
    gameWindow->show();
    gameWindow->gameMode=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    hide();
    gameWindow->show();
    gameWindow->gameMode=2;
}

void MainWindow::ButtonEnd_clicked()
{
    gameWindow->close();
    gameWindow=new GameWindow(this);
    connect(gameWindow,SIGNAL(endGame()),this,SLOT(ButtonEnd_clicked()));
    show();
}
