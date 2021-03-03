//
//  mainwindow.h
//  BattleShip Project GUI
//
//  Created by Vadim Juris on 22.03.18
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include <mainwindow.h>

namespace Ui {
    class MainWindow;
}

    /**
      * @brief MainWindow class
      * Creates a QDialog Window for the main menu, where user can choose between 3 different gamemodes;
      **/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow Constructor: creates the main menu window;
     **/
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief MainWindow Destructor;
     **/
    ~MainWindow();

private slots:

    /**
     * @brief hides MainWindow, shows GameWindow with gamemode 0 (Player vs Player);
     **/
    void on_pushButton_clicked();

    /**
     * @brief hides MainWindow, shows GameWindow with gamemode 1 (Player vs easy AI);
     **/
    void on_pushButton_2_clicked();

    /**
     * @brief hides MainWindow, shows GameWindow with gamemode 2 (Player vs normal AI);
     **/
    void on_pushButton_3_clicked();

    /**
     * @brief creates a new GameWindow (but doesn't show it yet) after clicking "Spiel beenden" QPushButton in GameWindow;
     **/
    void ButtonEnd_clicked();

private:

    /**
     * @brief creates MainWindow ui;
     **/
    Ui::MainWindow *ui;

    /**
     * @brief pointer to gameWindow object;
     **/
    GameWindow *gameWindow;
};

#endif // MAINWINDOW_H
