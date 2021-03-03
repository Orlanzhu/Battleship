//
//  gameboard.hpp
//  BattleShip Project Logic
//
//  Created by Rui Zhu on 18.03.18. Latest update on 21.03.18.
//  Copyright © 2018 Rui Zhu. All rights reserved.
//

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP
#include <memory>
#include <array>
#include <vector>

/**
 * @brief The GameBoard class
 * GameBoard Class implements the gameboards for two players; contains Ship Class; allows players to place ships via placeShip method;
 * allows players to shoot at enemy ships via checkHit method
 *
 **/
class GameBoard {
public:

    /**
     * @brief The status enum represents the four status of the GameBoard grids:
     * 1.sea(not occupied);
     * 2.hit(grid shot by opponents is occupied by a ship);
     * 3.miss(grid shot by opponents is not occupied by a ship);
     * 4.boat(grid is occupied by a ship);
     */
    enum status{sea,hit,miss,boat};

    /**
     * @brief GameBoard Constructor: Initializes a gameboard with 10x10 vector girds with default value of 'sea'
     * Carrier number:0, Destroyer number:0, Submarine number:0, total Ship number:0
     */
    GameBoard();

    ///public slots:
    /**
     * @brief checkPlace checks if the chosen starting grid is valid to place a ship of size PlaceSize in four directions: right, left, up and down
     * @param x coordinate of the chosen grid
     * @param y coordinate of the chosen grid
     * @return a one-dimensional boolean array with four values to show the validities of placement in four directions
     */
    std::array< bool, 4> checkPlace(int x, int y);

    /**
     * @brief placeShip places the ships after the chosen starting grid has been confirmed and the valid placement direction is chosen
     * @param dir a valid direction of placement chosen by the player
     */
    void placeShip(int dir);

    /**
     * @brief randomPlace initializes the starting positions of the ships randomly on the game board
     */
    void randomPlace();

    /**
     * @brief checkHit checks if an attack has hit a ship
     * @param x coordinate of the shot
     * @param y coordinate of the shot
     * @return the enum status of the grid in int after the shot or an integer value of 666 for Game Over
     */
    int checkHit(int x, int y);

    /**
     * @brief setHit checks the HP of a ship shot and also if the hit ship is sunken, reducing the ship number in the game board accordingly
     * @param x coordinate of the hit shot
     * @param y coordinate of the hit shot
     */
    void setHit(int x, int y);

    /**
     * @brief GameBoard::easyAIshoot takes random shots at the player's game board
     * @return coordinates of the AI shot
     */
    std::array<int,2> easyAIshoot();

    /**
     * @brief AIshoot takes calculated shots at the player's game board
     * @return coordinates of the AI shot
     */
    std::array<int,2> AIshoot();

    /**
     * @brief getShipNo gets the total ship number(ShipNo) on the game board
     * @return the remaining ship number on the game board
     */
    int getShipNo() const;

    /**
     * @brief getCarNo gets the current carrier number on the game board
     * @return the current carrier number on the game board
     */
    int getCarNo() const;

    /**
     * @brief getCruNo gets the current cruiser number on the game board
     * @return the current cruiser number on the game board
     */
    int getCruNo() const;

    /**
     * @brief getDesNo gets the current destroyer number on the game board
     * @return the current destroyer number on the game board
     */
    int getDesNo() const;

    /**
     * @brief getSubNo gets the current submarine number on the game board
     * @return the current submarine number on the game board
     */
    int getSubNo() const;

    /**
     * @brief getGrid gets the enum status of a grid on the gameboard
     * @param x coordinate of the grid
     * @param y coordinate of the grid
     * @return the enum status in int of the grid
     */
    int getGrid(int x, int y) const;

    /**
     * @brief get current PlaceSize for placement
     * @return current PlaceSize
     */
    int getPlaceSize() const;

    /**
     * @brief isGameOver checks if the game if over
     * @return True for Game Over, False if not
     */
    bool isGameOver();

    /**
     * @brief produce a random integer number
     * @param min lower bound of the range of the random number
     * @param max upper bound of the range of the random number
     * @return the random number within the range
     */
    int getNumber(int min, int max);

private:

    /**
     * @brief The nested class of GameBoard: Ship class implements the different types of ships on the game board
     */
    class Ship {
    public:

        /**
         * @brief The shipsize enum represents the different sizes for the four different types of ships
         */
        enum shipsize {Car = 5, Cru = 4, Des = 3, Sub = 2};

        /**
         * @brief Ship Constructor initializes a ship Object
         * @param size of the ship in enum shipsize
         * @param x coordinate of the starting coordinate of the ship
         * @param y coordinate of the starting coordinate of the ship
         * @param dir direction of placement of the ship
         */
        Ship(shipsize size, int x, int y, int dir);

        /**
         * @brief getHP gets the HP of a ship
         * @return the HP of the ship
         */
        int getHP() const;

        /**
         * @brief setHP sets the HP of a ship when the ship is hit
         */
        void setHP();

        /**
         * @brief getSize gets the size of a ship
         * @return the size of the ship
         */
        int getSize() const;

        /**
         * @brief checkSunk checks if a ship is sunken
         * @return the boolean sunk status of the ship
         */
        bool checkSunk() const;

        /**
         * @brief setSunk changes the sunk status of a ship to true
         */
        void setSunk();

        /**
         * @brief LocationStPtx gets the x coordinate of the starting point of placement of a ship
         * @return x coordinate of the starting point of placement
         */
        int LocationStPtx() const;

        /**
         * @brief LocationStPty gets the y coordiante of the starting point of placement of a ship
         * @return y coordiante of the starting point of placement
         */
        int LocationStPty() const;

        /**
         * @brief getDir gets the direction of placement of a ship
         * @return the direction of placement of a ship
         */
        int getDir() const;

    private:

        /**
         * @brief size of the ship in terms of enum shipsize
         */
        shipsize size;

        /**
         * @brief sunk status of the ship
         */
        bool sunk;

        /**
         * @brief HP of the ship, with default starting value equvalent to the size of the ship
         */
        int HP;

        /**
         * @brief stPtx x coordinate of the starting point of placement, stPty y coordinate of the starting point of placement
         */
        const int stPtx, stPty;

        /**
         * @brief dir direction of placement of the ship
         *  direction: right=0; left=1; up=2; down=3;
         */
        const int dir;
    };

    /**
     * @brief grid is the two dimensional vector of the game board, containing the four possible status of the game board
     */
    std::vector<std::vector<status> > grid;

    /**
     * @brief CarNo carrier number in the game board;
     */
    int CarNo;

    /**
     * @brief CruNo cruiser number in the game board;
     */
    int CruNo;

    /**
     * @brief DesNo destroyer number in the game board;
     */
    int DesNo;

    /**
     * @brief SubNo submarine number in the game board;
     */
    int SubNo;

    /**
     * @brief ShipNo total ship number in the game board;
     */
    int ShipNo;

    /**
     * @brief PlaceSize current size of the ship to be placed in the game board
     */
    int PlaceSize;

    /**
     * @brief shiplist vector containing all 10 ships in the game board
     */
    std::vector<std::shared_ptr<Ship> > shiplist;

    /**
     * @brief curPos starting coordinates of the current postion of placement
     */
    std::array<int, 2> curPos;

};

#endif // GAMEBOARD_HPP

