/*
//+++++unused code for 10x10 field image coords++++++++

void GameWindow::mousePressEvent(QMouseEvent *event){
    int xCoord= event->x(); //from 0 to 9
    int yCoord= event->y(); //from 0 to 9
    int x, y;               //converted coordinates
    int f;                  //f=1 for Field1, f=2 for Field2
    //Field1 begins at x=50 y=100
    //Field2 begins at x=700 y=100
    if (xCoord>=50 && xCoord<=450 && yCoord>=100 && yCoord<=500) {  //Case for Field1
        x=(xCoord-50)/40;
        y=(yCoord-100)/40;checked
        f=1;
        qDebug()<<"x="<< x <<"y="<< y <<"Field"<<f;

    } else if (xCoord>=700 && xCoord<=1100 && yCoord>=100 && yCoord<=500) {  //Case for Field2
        x=(xCoord-700)/40;
        y=(yCoord-100)/40;
        f=2;
        qDebug()<<"x="<< x <<"y="<< y <<"Field"<<f;

    }    
}

    //+++connect all grid button signals to slots+++  //but34 = NEPAREIZI (button at x3 and y4), 0 min 9 max

    //int i;
    //mapValue[i] = 2;
    //connect(ui->but00, SIGNAL(clicked()), signalMapper, SLOT(map()));
    //signalMapper->setMapping(ui->but00, mapValue[1]);

    //connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(changeIndex(int)));

    //connect(ui->but00, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but10, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but20, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but30, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but40, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but50, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but60, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but70, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but80, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but90, SIGNAL(clicked()), this, SLOT(checked()));

    connect(ui->but01, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but11, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but21, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but31, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but41, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but51, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but61, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but71, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but81, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but91, SIGNAL(clicked()), this, SLOT(checked()));

    connect(ui->but02, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but12, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but22, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but32, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but42, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but52, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but62, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but72, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but82, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->but92, SIGNAL(clicked()), this, SLOT(checked()));

    //...
    //QPushButton *btnChk = (QPushButton *)sender();
    //++++++++++++++++++++++++++++++++++++++++++++++
    for (int i=0; i<10; i++){                //for x
        for (int j=0; j<10; j++){            //for y
            //QPushButton *but=new QPushButton(" ", this);
            int Ver=10;
            int Hor=50;
            but->setGeometry(30*Ver,(30*Hor)+20,40,40);

            butMat1[i].push_back(but);
            butMat1[i][j]->setStyleSheet("background-color: rgb(155,201,247);"); //blue color
            connect(butMat1[i][j], SIGNAL(clicked()), this, SLOT(checked()));
        }
    }

//++++++++++++++++++++++++++++++++++++++++++++++

*/

#include "gameboard.hpp"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "main.cpp"

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QString>
#include <string>
#include <iostream>
#include <vector>
#include <array>


GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
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

    randBtn1 = new QPushButton("Schiffe zufallig platzieren");
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

void GameWindow::setButColorMat1()  //redraw board with actual coloring
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

void GameWindow::setButColorMat2()  //redraw board with actual coloring
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
                        break;
            }
        }
    }
}

void GameWindow::checkedField1(int row, int col)
{
    if (phase==2){
        x1=col;
        y1=row;
        board1.checkHit(y1,x1);
        setButEnemyMat1();
        if (static_cast<GameBoard::status>(board1.getGrid(y1,x1))!=1) {
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
        labelCru->setText(" Anzahl von übrige Schiffe: ");
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
        qDebug()<<"test"<<row<<col;
        x1=col;
        y1=row;
        lastPressX=col;
        lastPressY=row;
        disableButMat1();
            showPoss=board1.checkPlace(y1,x1);  //-board1.getPlaceSize()
            if ((showPoss[0]==false)&&(showPoss[1]==false)&&(showPoss[2]==false)&&(showPoss[3]==false)){
                enableButMat1();
                butMat1[col][row]->setStyleSheet("background-color: rgb(155,201,247);"
                                                 "min-width: 2em;"
                                                 "min-height: 2em;");
                --count;
            }
            if (showPoss[0]==true){
               butMat1[x1][y1+board1.getPlaceSize()-1]->setStyleSheet("background-color: yellow;"
                                    "min-width: 2em;"
                                    "min-height: 2em;");
               butMat1[x1][y1+board1.getPlaceSize()-1]->setEnabled(true);

            }
            if (showPoss[1]==true){
               butMat1[x1][y1-board1.getPlaceSize()+1]->setStyleSheet("background-color: yellow;"
                                    "min-width: 2em;"
                                    "min-height: 2em;");
               butMat1[x1][y1-board1.getPlaceSize()+1]->setEnabled(true);

            }
            if (showPoss[2]==true){
               butMat1[x1+board1.getPlaceSize()-1][y1]->setStyleSheet("background-color: yellow;"
                                    "min-width: 2em;"
                                    "min-height: 2em;");
               butMat1[x1+board1.getPlaceSize()-1][y1]->setEnabled(true);

            }
            if (showPoss[3]==true){
               butMat1[x1-board1.getPlaceSize()+1][y1]->setStyleSheet("background-color: yellow;"
                                    "min-width: 2em;"
                                    "min-height: 2em;");
               butMat1[x1-board1.getPlaceSize()+1][y1]->setEnabled(true);

            }
      }
    else if (count % 2==0){
           qDebug()<<"test"<<row<<col;
           x1=col;
           y1=row;
           if ((lastPressX==x1) && (lastPressY==y1-board1.getPlaceSize()+1)){
                dir=0;  //rechts
           } else if ((lastPressX==x1) && (lastPressY==y1+board1.getPlaceSize()-1)){
                dir=1;  //links
           } else if ((lastPressX==x1-board1.getPlaceSize()+1) && (lastPressY==y1)){
                dir=2;  //up
           } else if ((lastPressX==x1+board1.getPlaceSize()-1) && (lastPressY==y1)){
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
                   labelTurn->setText("              Spieler 2 Zug ->");
                   //---------------------------------------------------------------------------------------------------------
                   randBtn2 = new QPushButton("Schiffe zufallig platzieren");
                   ui->randPlaceBtn2->addWidget(randBtn2, 1, 1);
                   randBtn2->setFocusPolicy(Qt::NoFocus);
                   connect(randBtn2, &QPushButton::clicked, this, &GameWindow::placeRandField2);

               }
               else if ((gameMode==1)||(gameMode==2)){
                   ++phase;
                   setButEnemyMat2();
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
        if (((gameMode==1)||(gameMode==2)) && (count!=1000)){
            board2.randomPlace();
            count=1000;
        }
        x1=col;
        y1=row;
        board2.checkHit(y1,x1);
        setButEnemyMat2();
        if (static_cast<GameBoard::status>(board2.getGrid(y1,x1))!=1){  //ja nav hit
            if (gameMode==0){
                disableButMat2();
                ui->ButtonNext->setEnabled(true);
            }
            else if (gameMode==1){   //3rd button
                std::array<int,2> Coords=board1.AIshoot();
                setButColorMat1();

                while (static_cast<GameBoard::status>(board1.getGrid(Coords[0],Coords[1]))==1){
                    Coords=board1.AIshoot();
                    setButColorMat1();

                }
            }

            else if (gameMode==2){  //2nd button
                std::array<int,2> Coords=board1.easyAIshoot();
                setButColorMat1();

                while (static_cast<GameBoard::status>(board1.getGrid(Coords[0],Coords[1]))==1){
                    Coords=board1.easyAIshoot();
                    setButColorMat1();

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
        labelCru->setText(" Anzahl von übrige Schiffe: ");
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
      butMat2[col][row]->setStyleSheet("background-color: rgb(50,50,50);"  //   !!!SWAP X AND Y!!!
                                       "min-width: 2em;"
                                       "min-height: 2em;");
      qDebug()<<"test"<<row<<col;
      x1=col;
      y1=row;
      lastPressX=col;
      lastPressY=row;
      disableButMat2();
          showPoss=board2.checkPlace(y1,x1);  //-board1.getPlaceSize()
          if ((showPoss[0]==false)&&(showPoss[1]==false)&&(showPoss[2]==false)&&(showPoss[3]==false)){
              enableButMat2();
              butMat2[col][row]->setStyleSheet("background-color: rgb(155,201,247);"
                                               "min-width: 2em;"
                                               "min-height: 2em;");
              --count;
          }
          if (showPoss[0]==true){
             butMat2[x1][y1+board2.getPlaceSize()-1]->setStyleSheet("background-color: yellow;"
                                  "min-width: 2em;"
                                  "min-height: 2em;");
             butMat2[x1][y1+board2.getPlaceSize()-1]->setEnabled(true);

          }
          if (showPoss[1]==true){
             butMat2[x1][y1-board2.getPlaceSize()+1]->setStyleSheet("background-color: yellow;"
                                  "min-width: 2em;"
                                  "min-height: 2em;");
             butMat2[x1][y1-board2.getPlaceSize()+1]->setEnabled(true);

          }
          if (showPoss[2]==true){
             butMat2[x1+board2.getPlaceSize()-1][y1]->setStyleSheet("background-color: yellow;"
                                  "min-width: 2em;"
                                  "min-height: 2em;");
             butMat2[x1+board2.getPlaceSize()-1][y1]->setEnabled(true);

          }
          if (showPoss[3]==true){
             butMat2[x1-board2.getPlaceSize()+1][y1]->setStyleSheet("background-color: yellow;"
                                  "min-width: 2em;"
                                  "min-height: 2em;");
             butMat2[x1-board2.getPlaceSize()+1][y1]->setEnabled(true);

          }
    }
    else if (count % 2==0){
         qDebug()<<"test"<<row<<col;
         x1=col;
         y1=row;
         if ((lastPressX==x1) && (lastPressY==y1-board2.getPlaceSize()+1)){
              dir=0;  //rechts
         } else if ((lastPressX==x1) && (lastPressY==y1+board2.getPlaceSize()-1)){
              dir=1;  //links
         } else if ((lastPressX==x1-board2.getPlaceSize()+1) && (lastPressY==y1)){
              dir=2;  //up
         } else if ((lastPressX==x1+board2.getPlaceSize()-1) && (lastPressY==y1)){
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
             labelTurn->setText("              Spieler 1 Zug ->");
             labelPhase->setText("              Kampfphase!");
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
    } else if (count2 % 2==0){
        enableButMat2();
        setButEnemyMat2();
        setButColorMat1();
        labelTurn->setText("              Spieler 1 Zug ->");
        ui->ButtonNext->setEnabled(false);
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
    //-----------------------------------------------------------------
    if (gameMode==0){
        randBtn2 = new QPushButton("Schiffe zufallig platzieren");
        ui->randPlaceBtn2->addWidget(randBtn2, 1, 1);
        randBtn2->setFocusPolicy(Qt::NoFocus);
        connect(randBtn2, &QPushButton::clicked, this, &GameWindow::placeRandField2);
    } else if ((gameMode==1)||(gameMode==2)){
        ++phase;
        setButEnemyMat2();
        setButColorMat1();
    labelTurn->setText("              Spieler 1 Zug ->");
    }
}

void GameWindow::placeRandField2(){
    setButColorMat1();
    enableButMat2();
    setButEnemyMat2();
    labelTurn->setText("              Spieler 1 Zug ->");
    labelPhase->setText("              Kampfphase!");
    ++phase;
    board2.randomPlace();
    randBtn2->deleteLater();
}

