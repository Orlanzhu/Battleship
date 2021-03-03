
#include "gameboard.hpp"
#include "gamewindow.h"
#include "mainwindow.h"
#include "ui_gamewindow.h"
#include "main.cpp"

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QString>
#include <iostream>
#include <vector>
#include <array>


GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    checkstate=1;
    phase=1;
    count=1;
    count2=1;
    ui->setupUi(this);
    ui->ButtonNext->setEnabled(false);
    this->generateMat1();
    this->generateMat2();
    disableButMat2();
    hideButMat2();

    labelTurn = new QLabel ("              <- Spieler 1 Zug");
    ui->whichTurn->addWidget(labelTurn, 1,1);
    labelPhase = new QLabel("       Schiff Platzierungsphase!");
    ui->whichPhase->addWidget(labelPhase, 1, 1);

    labelCar = new QLabel("  Schlachtschiff:         ");
    ui->statusLog->addWidget(labelCar, 1, 1);
    labelCru = new QLabel("  Kreuzer:                ");
    ui->statusLog->addWidget(labelCru, 2, 1);
    labelDes = new QLabel("  Zerstörer:              ");
    ui->statusLog->addWidget(labelDes, 3, 1);
    labelSub = new QLabel("  U-Boote:                ");
    ui->statusLog->addWidget(labelSub, 4, 1);

    labelTempCar = new QLabel(QString::number(board1.getCarNo()));
    ui->statusLog->addWidget(labelTempCar, 1, 2);
    labelTempCru = new QLabel(QString::number(board1.getCruNo()));
    ui->statusLog->addWidget(labelTempCru, 2, 2);
    labelTempDes = new QLabel(QString::number(board1.getDesNo()));
    ui->statusLog->addWidget(labelTempDes, 3, 2);
    labelTempSub = new QLabel(QString::number(board1.getSubNo()));
    ui->statusLog->addWidget(labelTempSub, 4, 2);

    randBtn1 = new QPushButton("Schiffe zufällig platzieren");
    ui->randPlaceBtn1->addWidget(randBtn1, 1, 1);
    randBtn1->setFocusPolicy(Qt::NoFocus);
    connect(randBtn1, &QPushButton::clicked, this, &GameWindow::placeRandField1);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::getShipNoLabels1(){
    labelTempCar->setText(QString::number(board1.getCarNo()));
    labelTempCru->setText(QString::number(board1.getCruNo()));
    labelTempDes->setText(QString::number(board1.getDesNo()));
    labelTempSub->setText(QString::number(board1.getSubNo()));
}

void GameWindow::getShipNoLabels2(){
    labelTempCar->setText(QString::number(board2.getCarNo()));
    labelTempCru->setText(QString::number(board2.getCruNo()));
    labelTempDes->setText(QString::number(board2.getDesNo()));
    labelTempSub->setText(QString::number(board2.getSubNo()));
}

void GameWindow::generateMat1()
{
    butMat1.resize(10);
    for(int rowT = 0; rowT < 10; ++rowT) {
        butMat1.push_back(std::vector<QPushButton*>());
        for(int col = 0; col < 10; ++col) {
            auto btn = new QPushButton("");
            btn->setStyleSheet("background-color: rgb(155,201,247);"
                               "min-width: 2em;"
                               "min-height: 2em;");
            btn->setFocusPolicy(Qt::NoFocus);
            ui->field1->addWidget(btn, rowT, col);
            int row;
            switch(rowT){
                case 0: row=9; break;
                case 1: row=8; break;
                case 2: row=7; break;
                case 3: row=6; break;
                case 4: row=5; break;
                case 5: row=4; break;
                case 6: row=3; break;
                case 7: row=2; break;
                case 8: row=1; break;
                case 9: row=0; break;
            }
            connect(btn, &QPushButton::clicked, this, [=](){emit signal1(col,row);});
            butMat1[row].push_back(btn);
        }
    }
    connect(this, &GameWindow::signal1, this, &GameWindow::checkedField1);
}

void GameWindow::generateMat2()
{
    butMat2.resize(10);
    for(int rowT = 0; rowT < 10; ++rowT) {
        butMat2.push_back(std::vector<QPushButton*>());
        for(int col = 0; col < 10; ++col) {
            auto btn = new QPushButton("");
            btn->setStyleSheet("background-color: rgb(155,201,247);"
                               "min-width: 2em;"
                               "min-height: 2em;");
            btn->setFocusPolicy(Qt::NoFocus);
            ui->field2->addWidget(btn, rowT, col);
            int row;
            switch(rowT){
                case 0: row=9; break;
                case 1: row=8; break;
                case 2: row=7; break;
                case 3: row=6; break;
                case 4: row=5; break;
                case 5: row=4; break;
                case 6: row=3; break;
                case 7: row=2; break;
                case 8: row=1; break;
                case 9: row=0; break;
            }
            connect(btn, &QPushButton::clicked, this, [=](){emit signal2(col,row);});
            butMat2[row].push_back(btn);
        }
    }
    connect(this, &GameWindow::signal2, this, &GameWindow::checkedField2);
}

void GameWindow::disableButMat1()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat1[i][j]->setEnabled(false);
        }
    }
}

void GameWindow::disableButMat2()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat2[i][j]->setEnabled(false);
        }
    }
}

void GameWindow::enableButMat1()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat1[i][j]->setEnabled(true);
        }
    }
}

void GameWindow::enableButMat2()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat2[i][j]->setEnabled(true);
        }
    }
}

void GameWindow::hideButMat1()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat1[j][i]->setStyleSheet("background-color: rgb(220,220,220);"
                                         "min-width: 2em;"
                                         "min-height: 2em;");
        }
    }
}

void GameWindow::hideButMat2()
{
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            butMat2[j][i]->setStyleSheet("background-color: rgb(220,220,220);"
                                         "min-width: 2em;"
                                         "min-height: 2em;");
        }
    }
}

void GameWindow::setButColorMat1()
{
    int state;
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            state=static_cast<GameBoard::status>(board1.getGrid(i,j));
            switch (state){
                //Sea - blue
                case 0: butMat1[j][i]->setStyleSheet("background-color: rgb(155,201,247);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Hit - red
                case 1: butMat1[j][i]->setStyleSheet("background-color: rgb(220,0,0);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Miss - gray
                case 2: butMat1[j][i]->setStyleSheet("background-color: rgb(150,150,150);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Boat - black
                case 3: butMat1[j][i]->setStyleSheet("background-color: rgb(50,50,50);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat1[j][i]->setEnabled(false);
                        break;
            }
        }
    }
}

void GameWindow::setButColorMat2()
{
    int state;
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            state=static_cast<GameBoard::status>(board2.getGrid(i,j));
            switch (state){
                //Sea - blue
                case 0: butMat2[j][i]->setStyleSheet("background-color: rgb(155,201,247);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Hit - red
                case 1: butMat2[j][i]->setStyleSheet("background-color: rgb(220,0,0);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Miss - gray
                case 2: butMat2[j][i]->setStyleSheet("background-color: rgb(150,150,150);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
                //Boat - black
                case 3: butMat2[j][i]->setStyleSheet("background-color: rgb(50,50,50);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat2[j][i]->setEnabled(false);
                        break;
            }
        }
    }
}

void GameWindow::setButEnemyMat1()
{
    int state;
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            state=static_cast<GameBoard::status>(board1.getGrid(i,j));
            switch (state){
                //Hit - red
                case 1: butMat1[j][i]->setStyleSheet("background-color: rgb(220,0,0);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat1[j][i]->setEnabled(false);                        
                        break;
                //Miss - gray
                case 2: butMat1[j][i]->setStyleSheet("background-color: rgb(150,150,150);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat1[j][i]->setEnabled(false);
                        break;
                //Sea and boat - blue
                default:butMat1[j][i]->setStyleSheet("background-color: rgb(155,201,247);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        break;
            }
        }
    }
}

void GameWindow::setButEnemyMat2()
{
    int state;
    for (int j=9;j>-1;j--){
        for (int i=0;i<10;i++) {
            state=static_cast<GameBoard::status>(board2.getGrid(i,j));
            switch (state){
                //Hit - red
                case 1: butMat2[j][i]->setStyleSheet("background-color: rgb(220,0,0);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat2[j][i]->setEnabled(false);
                        break;
                //Miss - gray
                case 2: butMat2[j][i]->setStyleSheet("background-color: rgb(150,150,150);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat2[j][i]->setEnabled(false);
                        break;
                //Sea and boat - blue
                default:butMat2[j][i]->setStyleSheet("background-color: rgb(155,201,247);"
                                                     "min-width: 2em;"
                                                     "min-height: 2em;");
                        butMat2[j][i]->setEnabled(true);
                        break;
            }
        }
    }
}

void GameWindow::checkedField1(int row, int col)
{
    if (phase==2){
        board1.checkHit(row,col);
        setButEnemyMat1();
        if (static_cast<GameBoard::status>(board1.getGrid(row,col))!=1) {
            disableButMat1();
            ui->ButtonNext->setEnabled(true);
        }
        if (board1.getShipNo()==0){
            labelTurn->setText("          Spieler 2 hat gewonnen!");
            disableButMat1();
            disableButMat2();
        }
        labelCar->setText("                          ");
        ui->statusLog->addWidget(labelCar, 1, 1);
        labelCru->setText(" Feindliche Schiffe übrig: ");
        ui->statusLog->addWidget(labelCru, 2, 1);
        labelDes->setText("                          ");
        ui->statusLog->addWidget(labelDes, 3, 1);
        labelSub->setText("                          ");
        labelTempCar->setText(" ");
        labelTempCru->setText(QString::number(board1.getShipNo()));
        labelTempDes->setText(" ");
        labelTempSub->setText(" ");
    }
    else if (count % 2==1){
        butMat1[col][row]->setStyleSheet("background-color: rgb(50,50,50);"  //   !!!SWAP X AND Y!!!
                                         "min-width: 2em;"
                                         "min-height: 2em;");
        //qDebug()<<"test"<<row<<col;
        lastPressX=col;
        lastPressY=row;
        disableButMat1();
            showPoss=board1.checkPlace(row,col);  //-board1.getPlaceSize()
            if ((showPoss[0]==false)&&(showPoss[1]==false)&&(showPoss[2]==false)&&(showPoss[3]==false)){
                enableButMat1();
                butMat1[col][row]->setStyleSheet("background-color: rgb(155,201,247);"
                                                 "min-width: 2em;"
                                                 "min-height: 2em;");
                --count;
            }
            if (showPoss[0]==true){
               butMat1[col][row+board1.getPlaceSize()-1]->setStyleSheet("background-color: yellow;"
                                                                        "min-width: 2em;"
                                                                        "min-height: 2em;");
               butMat1[col][row+board1.getPlaceSize()-1]->setEnabled(true);

            }
            if (showPoss[1]==true){
               butMat1[col][row-board1.getPlaceSize()+1]->setStyleSheet("background-color: yellow;"
                                                                        "min-width: 2em;"
                                                                        "min-height: 2em;");
               butMat1[col][row-board1.getPlaceSize()+1]->setEnabled(true);

            }
            if (showPoss[2]==true){
               butMat1[col+board1.getPlaceSize()-1][row]->setStyleSheet("background-color: yellow;"
                                                                        "min-width: 2em;"
                                                                        "min-height: 2em;");
               butMat1[col+board1.getPlaceSize()-1][row]->setEnabled(true);
            }
            if (showPoss[3]==true){
               butMat1[col-board1.getPlaceSize()+1][row]->setStyleSheet("background-color: yellow;"
                                                                        "min-width: 2em;"
                                                                        "min-height: 2em;");
               butMat1[col-board1.getPlaceSize()+1][row]->setEnabled(true);
            }
      }
    else if (count % 2==0){
           //qDebug()<<"test"<<row<<col;
           if ((lastPressX==col) && (lastPressY==row-board1.getPlaceSize()+1)){
                dir=0;  //right
           } else if ((lastPressX==col) && (lastPressY==row+board1.getPlaceSize()-1)){
                dir=1;  //left
           } else if ((lastPressX==col-board1.getPlaceSize()+1) && (lastPressY==row)){
                dir=2;  //up
           } else if ((lastPressX==col+board1.getPlaceSize()-1) && (lastPressY==row)){
                dir=3;  //down
           }
           board1.placeShip(dir);
           enableButMat1();
           setButColorMat1();
           getShipNoLabels1();
           if (board1.getShipNo()==10){
               randBtn1->deleteLater();
               if (gameMode==0){
                   count=0;
                   hideButMat1();
                   setButColorMat2();
                   getShipNoLabels2();
                   labelTurn->setText("              Spieler 2 Zug ->");
                   randBtn2 = new QPushButton("Schiffe zufällig platzieren");
                   ui->randPlaceBtn2->addWidget(randBtn2, 1, 1);
                   randBtn2->setFocusPolicy(Qt::NoFocus);
                   connect(randBtn2, &QPushButton::clicked, this, &GameWindow::placeRandField2);
               }
               else if ((gameMode==1)||(gameMode==2)){
                   ++phase;
                   setButEnemyMat2();
                   labelCar->setText("                          ");
                   labelCru->setText(" Feindliche Schiffe übrig: ");
                   labelDes->setText("                          ");
                   labelSub->setText("                          ");
                   labelTempCar->setText(" ");
                   labelTempCru->setText(QString::number(board1.getShipNo()));
                   labelTempDes->setText(" ");
                   labelTempSub->setText(" ");
               }
               enableButMat2();
               disableButMat1();
            }
      }
    ++count;
}

void GameWindow::checkedField2(int row, int col)
{
    if (phase==2){
        if ((gameMode==1)||(gameMode==2)){
            if (checkstate==1){
                board2.randomPlace();
                ++checkstate;
                labelTurn->setText("              Spieler 1 Zug ->");
            }
        }
        board2.checkHit(row,col);
        setButEnemyMat2();
        if (static_cast<GameBoard::status>(board2.getGrid(row,col))!=GameBoard::hit){  //in case there is no hit
            if (gameMode==0){
                disableButMat2();
                ui->ButtonNext->setEnabled(true);
            }
            else if (gameMode==1){   //3rd button
                std::array<int,2> Coords=board1.AIshoot();
                setButColorMat1();
                while (static_cast<GameBoard::status>(board1.getGrid(Coords[0],Coords[1]))==GameBoard::hit){
                    Coords=board1.AIshoot();
                    setButColorMat1();
                }
                if (board1.getShipNo()==0){
                    labelTurn->setText("       Computer hat gewonnen!");
                    disableButMat1();
                    disableButMat2();
                }
            }
            else if (gameMode==2){   //2nd button
                std::array<int,2> Coords=board1.easyAIshoot();
                setButColorMat1();
                while (static_cast<GameBoard::status>(board1.getGrid(Coords[0],Coords[1]))==GameBoard::hit){
                    Coords=board1.easyAIshoot();
                    setButColorMat1();
                }
                if (board1.getShipNo()==0){
                    labelTurn->setText("        Computer hat gewonnen!");
                    disableButMat1();
                    disableButMat2();
                }
            }
        }
        if (board2.getShipNo()==0){
            labelTurn->setText("          Spieler 1 hat gewonnen!");
            disableButMat1();
            disableButMat2();
        }
        labelCar->setText("                          ");
        ui->statusLog->addWidget(labelCar, 1, 1);
        labelCru->setText(" Feindliche Schiffe übrig: ");
        ui->statusLog->addWidget(labelCru, 2, 1);
        labelDes->setText("                          ");
        ui->statusLog->addWidget(labelDes, 3, 1);
        labelSub->setText("                          ");
        labelTempCar->setText(" ");
        labelTempCru->setText(QString::number(board2.getShipNo()));
        labelTempDes->setText(" ");
        labelTempSub->setText(" ");
    }
    else if (count % 2==1){
      butMat2[col][row]->setStyleSheet("background-color: rgb(50,50,50);"
                                       "min-width: 2em;"
                                       "min-height: 2em;");
      //qDebug()<<"test"<<row<<col;
      lastPressX=col;
      lastPressY=row;
      disableButMat2();
          showPoss=board2.checkPlace(row,col);
          if ((showPoss[0]==false)&&(showPoss[1]==false)&&(showPoss[2]==false)&&(showPoss[3]==false)){
              enableButMat2();
              butMat2[col][row]->setStyleSheet("background-color: rgb(155,201,247);"
                                               "min-width: 2em;"
                                               "min-height: 2em;");
              --count;
          }
          if (showPoss[0]==true){
             butMat2[col][row+board2.getPlaceSize()-1]->setStyleSheet("background-color: yellow;"
                                                                      "min-width: 2em;"
                                                                      "min-height: 2em;");
             butMat2[col][row+board2.getPlaceSize()-1]->setEnabled(true);
          }
          if (showPoss[1]==true){
             butMat2[col][row-board2.getPlaceSize()+1]->setStyleSheet("background-color: yellow;"
                                                                      "min-width: 2em;"
                                                                      "min-height: 2em;");
             butMat2[col][row-board2.getPlaceSize()+1]->setEnabled(true);
          }
          if (showPoss[2]==true){
             butMat2[col+board2.getPlaceSize()-1][row]->setStyleSheet("background-color: yellow;"
                                                                      "min-width: 2em;"
                                                                      "min-height: 2em;");
             butMat2[col+board2.getPlaceSize()-1][row]->setEnabled(true);
          }
          if (showPoss[3]==true){
             butMat2[col-board2.getPlaceSize()+1][row]->setStyleSheet("background-color: yellow;"
                                                                      "min-width: 2em;"
                                                                      "min-height: 2em;");
             butMat2[col-board2.getPlaceSize()+1][row]->setEnabled(true);
          }
    }
    else if (count % 2==0){
         //qDebug()<<"test"<<row<<col;
         if ((lastPressX==col) && (lastPressY==row-board2.getPlaceSize()+1)){
              dir=0;  //rechts
         } else if ((lastPressX==col) && (lastPressY==row+board2.getPlaceSize()-1)){
              dir=1;  //links
         } else if ((lastPressX==col-board2.getPlaceSize()+1) && (lastPressY==row)){
              dir=2;  //up
         } else if ((lastPressX==col+board2.getPlaceSize()-1) && (lastPressY==row)){
              dir=3;  //down
         }
         board2.placeShip(dir);
         enableButMat2();
         setButColorMat2();
         getShipNoLabels2();
         if (board2.getShipNo()==10){
             randBtn2->deleteLater();
             setButColorMat1();
             enableButMat2();
             setButEnemyMat2();
             ui->statusLog->addWidget(labelCar, 1, 1);
             labelCru->setText(" Feindliche Schiffe übrig: ");
             ui->statusLog->addWidget(labelCru, 2, 1);
             labelDes->setText("                          ");
             ui->statusLog->addWidget(labelDes, 3, 1);
             labelSub->setText("                          ");
             labelTempCar->setText(" ");
             labelTempCru->setText(QString::number(board2.getShipNo()));
             labelTempDes->setText(" ");
             labelTempSub->setText(" ");
             labelTurn->setText("              Spieler 1 Zug ->");
             labelPhase->setText("               Kampfphase!");
             ++phase;
         }
    }
    ++count;
}

void GameWindow::on_ButtonNext_clicked()
{
    if (count2 % 2==1){
        enableButMat1();
        setButEnemyMat1();
        setButColorMat2();
        labelTurn->setText("              <- Spieler 2 Zug");
        ui->ButtonNext->setEnabled(false);
        labelCar->setText("                          ");
        labelCru->setText(" Feindliche Schiffe übrig: ");
        labelDes->setText("                          ");
        labelSub->setText("                          ");
        labelTempCar->setText(" ");
        labelTempCru->setText(QString::number(board1.getShipNo()));
        labelTempDes->setText(" ");
        labelTempSub->setText(" ");
    } else if (count2 % 2==0){
        enableButMat2();
        setButEnemyMat2();
        setButColorMat1();
        labelTurn->setText("              Spieler 1 Zug ->");
        ui->ButtonNext->setEnabled(false);
        labelCar->setText("                          ");
        labelCru->setText(" Feindliche Schiffe übrig: ");
        labelDes->setText("                          ");
        labelSub->setText("                          ");
        labelTempCar->setText(" ");
        labelTempCru->setText(QString::number(board2.getShipNo()));
        labelTempDes->setText(" ");
        labelTempSub->setText(" ");
    }
    ++count2;
}

void GameWindow::placeRandField1(){
    enableButMat2();
    disableButMat1();
    hideButMat1();
    setButColorMat2();
    labelTurn->setText("              Spieler 2 Zug ->");
    board1.randomPlace();
    randBtn1->deleteLater();
    if (gameMode==0){
        randBtn2 = new QPushButton("Schiffe zufällig platzieren");
        ui->randPlaceBtn2->addWidget(randBtn2, 1, 1);
        randBtn2->setFocusPolicy(Qt::NoFocus);
        connect(randBtn2, &QPushButton::clicked, this, &GameWindow::placeRandField2);
    } else if ((gameMode==1)||(gameMode==2)){
        ++phase;
        setButEnemyMat2();
        setButColorMat1();
        labelPhase->setText("               Kampfphase!");
        labelTurn->setText("              Spieler 1 Zug ->");
        labelCar->setText("                          ");
        labelCru->setText(" Feindliche Schiffe übrig: ");
        labelDes->setText("                          ");
        labelSub->setText("                          ");
        labelTempCar->setText(" ");
        labelTempCru->setText(QString::number(board1.getShipNo()));
        labelTempDes->setText(" ");
        labelTempSub->setText(" ");
    }
}

void GameWindow::placeRandField2(){
    setButColorMat1();
    enableButMat2();
    setButEnemyMat2();
    labelTurn->setText("              Spieler 1 Zug ->");
    labelPhase->setText("               Kampfphase!");
    ++phase;
    board2.randomPlace();
    labelCar->setText("                          ");
    labelCru->setText(" Feindliche Schiffe übrig: ");
    labelDes->setText("                          ");
    labelSub->setText("                          ");
    labelTempCar->setText(" ");
    labelTempCru->setText(QString::number(board1.getShipNo()));
    labelTempDes->setText(" ");
    labelTempSub->setText(" ");
    randBtn2->deleteLater();
}

void GameWindow::on_ButtonEnd_clicked()
{
    emit endGame();
}
