#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
        hide();
        gameWindow.show();
        gameWindow.gameMode=0;
}

void MainWindow::on_pushButton_2_clicked()
{
        hide();
        gameWindow.show();
        gameWindow.gameMode=1;
}

void MainWindow::on_pushButton_3_clicked()
{
        hide();
        gameWindow.show();
        gameWindow.gameMode=2;
}

