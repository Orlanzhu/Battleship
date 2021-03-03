//
//  gamewindow.h
//  BattleShip Project GUI
//
//  Created by Vadim Juris on 22.03.18
//

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

/**
 * @brief GameWindow class
 * Creates a QDialog Window where the Game playing phase takes place;
 **/

class GameWindow : public QDialog
{
    Q_OBJECT

signals:

    /**
     * @brief emits a signal telling the coordinates of last pressed QPushButton on player 1 field (left side);
     * @param row saves the order of a grid element in a row, essentially acts as x axis coordinate (in range from 0 to 9);
     * @param col saves the order of a grid element in a column, essentially acts as y axis coordinate (in range from 0 to 9);
     **/
    void signal1(int row, int col);

    /**
     * @brief emits a signal telling the coordinates of last pressed QPushButton on player 2 field (right side);
     * @param row saves the order of a grid element in a row, essentially acts as x axis coordinate (in range from 0 to 9);
     * @param col saves the order of a grid element in a column, essentially acts as y axis coordinate (in range from 0 to 9);
     **/
    void signal2(int row, int col);

    /**
     * @brief emits a signal that QPushButton "Spiel beenden" was pressed, afterwards Program goes back to MainWindow;
     **/
    void endGame();

public:

    /**
     * @brief GameWindow Constructor: creates the playing phase window, where 2-dimensional QPushButton vectors for every player field are created, Ship Placement phase QLabels are created and accordingly game phase is set to Ship Placement stage;
     **/
    explicit GameWindow(QWidget *parent = 0);

    /**
     * @brief GameWindow Destructor;
     **/
    ~GameWindow();

    /**
     * @brief generates a 2-dimensional QPushButton vector for player 1 field, creating signal slots alongside for every button on the field;
     **/
    void generateMat1();

    /**
     * @brief generates a 2-dimensional QPushButton vector for player 2 field, creating signal slots alongside for every button on the field;
     **/
    void generateMat2();

    /**
     * @brief sets text for QLabels, which show the number of already placed ships of every type on player 1 field (casting integer values to QString);
     **/
    void getShipNoLabels1();

    /**
     * @brief sets text for QLabels, which show the number of already placed ships of every type on player 2 field (casting integer values to QString);
     **/
    void getShipNoLabels2();

    /**
     * @brief disables all QPushButtons on player 1 field;
     **/
    void disableButMat1();

    /**
     * @brief disables all QPushButtons on player 2 field;
     **/
    void disableButMat2();


    /**
     * @brief enables all QPushButtons on player 1 field;
     **/
    void enableButMat1();

    /**
     * @brief enables all QPushButtons on player 2 field;
     **/
    void enableButMat2();

    /**
     * @brief "hides" all QPushButtons on player 1 field, by setting their color to gray;
     **/
    void hideButMat1();

    /**
     * @brief "hides" all QPushButtons on player 2 field, by setting their color to gray;
     **/
    void hideButMat2();

    /**
     * @brief sets QPushButton color on player 1 field according to current field status (for own player field):
     *        Sea - blue, Hit - red, Miss - gray, Boat - black (also disables QPushButtons with boat status, so that player can't place ships on already taken boxes);
     **/
    void setButColorMat1();

    /**
     * @brief sets QPushButton color on player 2 field according to current field status (for own player field):
     *        Sea - blue, Hit - red, Miss - gray, Boat - black (also disables QPushButtons with boat status, so that player can't place ships on already taken boxes);
     **/
    void setButColorMat2();

    /**
     * @brief sets QPushButton color on player 1 field according to current field status (for enemy player field):
     *        Hit - red, Miss - gray, Sea and Boat - blue (to hide ships);
     **/
    void setButEnemyMat1();

    /**
     * @brief sets QPushButton color on player 2 field according to current field status (for enemy player field):
     *        Hit - red, Miss - gray, Sea and Boat - blue (to hide ships);
     **/
    void setButEnemyMat2();

    /**
     * @brief sets text for QLabels, that shows the number of left enemy ships on player 1 field;
     **/
    void setShipsLeftLabels1();

    /**
     * @brief sets text for QLabels, that shows the number of left enemy ships on player 2 field;
     **/
    void setShipsLeftLabels2();

    /**
     * @brief boolean array, that shows the possibilites of ship placement;
     * @param showPoss[0]: if true, allows placing a ship along right direction;
     * @param showPoss[1]: if true, allows placing a ship along left direction;
     * @param showPoss[2]: if true, allows placing a ship along direction up;
     * @param showPoss[3]: if true, allows placing a ship along direction down;
     **/
    std::array< bool, 4> showPoss;

    /**
     * @brief count is used as player field QPushButton counter for clicks during Ship placement phase;
     **/
    int count;

    /**
     * @brief count is used as player field QPushButton counter for clicks during Shooting phase;
     **/
    int count2;

    /**
     * @brief for phase==1 the program is running in Ship placement phase, for phase==2 in Shooting phase;
     **/
    int phase;

    /**
     * @brief used to allow random ship placement only once when playing against AI (after random ship placement checkstate is incrimented to avoid if state being true);
     **/
    int checkstate;

    /**
     * @brief direction of placement of the ship
     *  direction: right=0; left=1; up=2; down=3;
     */
    int dir;

    /**
     * @brief each variable saves an according x and y coordinate of previously pressed QPushButton during ship placement phase (to know from to which box to draw a ship on the board);
     **/
    int lastPressX, lastPressY;

    /**
     * @brief sets game mode:
     * 0 for Player vs Player, 1 for Player vs easy AI, 2 for Player vs normal AI;
     **/
    int gameMode;

public slots:

    /**
     * @brief called after a QPushButton on field 1 is pressed with according row and col coordinates, does field redrawing, taking into account many if states (whether the game is in placement or shooting phase, playing vs human or AI, etc.);
     * @param row saves the order of a grid element in a row, essentially acts as x axis coordinate (in range from 0 to 9);
     * @param col saves the order of a grid element in a column, essentially acts as y axis coordinate (in range from 0 to 9);
     **/
    void checkedField1(int row, int col);

    /**
     * @brief called after a QPushButton on field 2 is pressed with according row and col coordinates, does field redrawing, taking into account many if states (whether the game is in placement or shooting phase, playing vs human or AI, etc.);
     * @param row saves the order of a grid element in a row, essentially acts as x axis coordinate (in range from 0 to 9);
     * @param col saves the order of a grid element in a column, essentially acts as y axis coordinate (in range from 0 to 9);
     **/
    void checkedField2(int row, int col);

private slots:

    /**
     * @brief does random ship placement on player 1 field, QPushButton is removed afterwards;
     **/
    void placeRandField1();

    /**
     * @brief does random ship placement on player 2 field, QPushButton is removed afterwards;
     **/
    void placeRandField2();

    /**
     * @brief actived after clicking "Nächste Zug" QPushButton, allows the turn for next player. Used when playing locally, so that every human player has time to "close eyes" after shooting;
     **/
    void on_ButtonNext_clicked();

    /**
     * @brief actived after clicking "Spiel beenden" QPushButton, program goes back to MainWindow;
     **/
    void on_ButtonEnd_clicked();

private:

    /**
     * @brief creates GameWindow ui;
     **/
    Ui::GameWindow *ui;

    /**
     * @brief object of gameboard for player 1;
     **/
    GameBoard board1;

    /**
     * @brief object of gameboard for player 2;
     **/
    GameBoard board2;

    /**
     * @brief text QLabel, showing which player's turn it is;
     **/
    QLabel* labelTurn;

    /**
     * @brief text QLabel, showing game phase is taking place;
     **/
    QLabel* labelPhase;

    /**
     * @brief text QLabel, prints "Schlachtschiff:";
     **/
    QLabel* labelCar;

    /**
     * @brief text QLabel, prints "Kreuzer:";
     **/
    QLabel* labelCru;

    /**
     * @brief text QLabel, prints "Zerstörer:";
     **/
    QLabel* labelDes;

    /**
     * @brief text QLabel, prints "U-Boote:";
     **/
    QLabel* labelSub;

    /**
     * @brief text QLabel, showing amount of Carrier ships left;
     **/
    QLabel* labelTempCar;

    /**
     * @brief text QLabel, showing amount of Cruiser ships left;
     **/
    QLabel* labelTempCru;

    /**
     * @brief text QLabel, showing amount of Destroyer ships left;
     **/
    QLabel* labelTempDes;

    /**
     * @brief text QLabel, showing amount of Submarine ships left;
     **/
    QLabel* labelTempSub;

    /**
     * @brief QPushButton for random ship placement on player 1 field,
     **/
    QPushButton* randBtn1;

    /**
     * @brief QPushButton for random ship placement on player 2 field,
     **/
    QPushButton* randBtn2;

    /**
     * @brief 2-dimensional vector of QPushButtons for player 1 field;
     **/
    std::vector<std::vector <QPushButton*> > butMat1;

    /**
     * @brief 2-dimensional vector of QPushButtons for player 2 field;
     **/
    std::vector<std::vector <QPushButton*> > butMat2;
};

#endif // GAMEWINDOW_H
