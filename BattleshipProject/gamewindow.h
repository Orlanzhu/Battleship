/*
 //++++unused mouse event++++++
 #include <QMouseEvent>
 void mousePressEvent(QMouseEvent *event);

 //++++unused QSignalMapper
 #include <QSignalMapper>
 signals:
     void clicked(int value);

 public Q_SLOTS:
     void changeIndex(int index);
 QSignalMapper *signalMapper;
 int mapValue[10];
*/

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <vector>
#include <iostream>
#include <gameboard.hpp>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

signals:
    void signal1(int row, int col);
    void signal2(int row, int col);
    void checkPlace(int row, int col);

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void generateMat1();  //erstellt public slots!
    void generateMat2();

    void getShipNoLabels1();        //no sejienes stuff bija zem public slots!!!!!!!!!!!!!!!!!!!
    void getShipNoLabels2();

    void disableButMat1();
    void disableButMat2();

    void enableButMat1();
    void enableButMat2();

    void hideButMat1();
    void hideButMat2();

    void setButColorMat1();
    void setButColorMat2();

    void setButEnemyMat1();  //same as setButColorMat1() but both boats and sea are blue
    void setButEnemyMat2();  //lidz sejienei stuff bija zem public slots!!!!!!!!!!

    std::array< bool, 4> showPoss;
    int x1, y1;
    int count;   //count in phase 1
    int count2;  //count in phase 2
    int phase;
    int dir;
    int lastPressX, lastPressY;
    int gameMode;  //0 for PvP, 1 for PvCPU

public slots:
    void checkedField1(int row, int col);
    void checkedField2(int row, int col);

private slots:
    void on_ButtonNext_clicked();

    void placeRandField1();
    void placeRandField2();

private:
    Ui::GameWindow *ui;
    GameBoard board1;
    GameBoard board2;
    QLabel* labelTurn;
    QLabel* labelPhase;
    QLabel* labelCar;
    QLabel* labelCru;
    QLabel* labelDes;
    QLabel* labelSub;
    QLabel* labelTempCar;
    QLabel* labelTempCru;
    QLabel* labelTempDes;
    QLabel* labelTempSub;

    QPushButton* randBtn1;
    QPushButton* randBtn2;

    std::vector<std::vector <QPushButton*> > butMat1;
    std::vector<std::vector <QPushButton*> > butMat2;
};

#endif // GAMEWINDOW_H
