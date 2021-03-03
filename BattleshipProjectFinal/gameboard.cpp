//
//  gameboard.cpp
//  BattleShip Project Logic
//
//  Created by Rui Zhu on 18.03.18. Latest update on 21.03.18.
//  Copyright © 2018 Rui Zhu. All rights reserved.
//

#include "gameboard.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <random>
#include <chrono>

///PlaceSize initialized at 0; current position of placement initialized at (0,0)
GameBoard::GameBoard(): grid(std::vector<std::vector<status> > (10, std::vector<status> (10, sea))),
CarNo(0), CruNo(0), DesNo(0), SubNo(0), ShipNo(0), PlaceSize(0), curPos({0,0})
{
}

//--------------------------------------------------Placement Phase-----------------------------------------------------//
std::array<bool,4> GameBoard::checkPlace(int x, int y){
    if (CarNo==0) PlaceSize=5;
    else if (CruNo<2) PlaceSize=4;
    else if (DesNo<3) PlaceSize=3;
    else if (SubNo<4) PlaceSize=2;

    std::array<bool,4> prf = {true, true, true, true};

    for (int i = x; i < x + PlaceSize; i++) {
        if (i > 9) {
            prf[0] = false;
            break;
        }

        if (grid[i][y] == boat) {
            prf[0] = false;
            break;
        }
    }

    for (int i = x; i > x - PlaceSize; i--) {
        if (i < 0 ) {
            prf[1] = false;
            break;
        }

        if (grid[i][y] == boat ) {
            prf[1] = false;
            break;
        }
    }

    for (int i = y; i < y + PlaceSize; i++) {
        if (i > 9) {
            prf[2] = false;
            break;
        }

        if (grid[x][i] == boat) {
            prf[2] = false;
            break;
        }
    }

    for (int i = y; i > y - PlaceSize; i--) {
        if (i < 0 ) {
            prf[3] = false;
            break;
        }

        if (grid[x][i] == boat) {
            prf[3] = false;
            break;
        }
    }

    curPos[0] = x; curPos[1] = y;
    return prf;
}


void GameBoard::placeShip(int dir) {
    int x = curPos[0];
    int y = curPos[1];

    if (dir == 0) {
        for (int i=x; i<x+PlaceSize; i++)
            grid[i][y] = boat;
    }

    if (dir == 1) {
        for (int i=x; i>x-PlaceSize; i--)
            grid[i][y] = boat;
    }

    if (dir == 2) {
        for (int i=y; i<y+PlaceSize; i++)
            grid[x][i] = boat;
    }

    if (dir == 3) {
        for (int i=y; i>y-PlaceSize; i--)
            grid[x][i] = boat;
    }

    switch(PlaceSize) {
        case 5:
            CarNo++;
            break;
        case 4:
            CruNo++;
            break;
        case 3:
            DesNo++;
            break;
        case 2:
            SubNo++;
            break;
    }

    ShipNo++;
    shiplist.push_back(std::make_shared<Ship> (static_cast<Ship::shipsize> (PlaceSize), curPos[0], curPos[1], dir));
}

void GameBoard::randomPlace() {
    int gr = 0; int randomPos = 0; int randomdir=0; std::array<bool,4> dirarray; int dir = 0;
    std::vector<std::array<int,2> > tmp(100,{0,0});

    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++){
            tmp[i*10+j] = {i,j};
        }
    }

    while (1) {
        if (ShipNo == 10) break;
        std::srand(static_cast<unsigned int>(std::time(0)));
        gr = tmp.size();
        randomPos = getNumber(0, gr);
        dirarray = checkPlace(tmp[randomPos][0],tmp[randomPos][1]);
        randomdir = getNumber(0, 4);
        for (int i = 0; i<4; i++) {
            if (dirarray[i] == true && randomdir == i) {
                dir = i;
                placeShip(dir);
                tmp.erase(tmp.begin()+randomPos);
                break;
            }
        }
    }
}

//--------------------------------------------------Shooting Phase------------------------------------------------------//
///check if hit for Board2(3) and Board4(1)
int GameBoard::checkHit(int x, int y){
    if (grid[x][y] == boat) {
        grid[x][y] = hit;
        setHit(x,y);
        if (isGameOver()) return 666;
        ///emit signals
        //emit a( ,  )
    } else if (grid[x][y] == sea){
        grid[x][y] = miss;
    }
    return static_cast<int> (grid[x][y]);
}

///search all ships to determine which one is hit
void GameBoard::setHit(int x, int y){
    for (auto &it: shiplist) {
        int gr = static_cast<int>(it->getSize());

        if(it->getDir() == 0) {
            for(int i = it-> LocationStPtx(); i < it->LocationStPtx()+gr; i++) {
                if(i == x && it->LocationStPty() == y) {
                    it->setHP();
                    if (it->checkSunk()  == true) {
                        ShipNo--;
                    }
                }
            }
        }

        if(it->getDir() == 1) {
            for(int i = it-> LocationStPtx(); i > it->LocationStPtx()-gr; i--) {
                if(i == x && it->LocationStPty() == y) {
                    it->setHP();
                    if (it->checkSunk()  == true) {
                        ShipNo--;
                    }
                }
            }
        }

        if(it->getDir() == 2) {
            for(int i = it-> LocationStPty(); i < it->LocationStPty()+gr; i++) {
                if(it->LocationStPtx() == x && i == y) {
                    it->setHP();
                    if (it->checkSunk()  == true) {
                        ShipNo--;
                    }
                }
            }
        }

        if (it->getDir() == 3){
            for(int i = it->LocationStPty(); i > it->LocationStPty()-gr; i--) {
                if(it->LocationStPtx() == x && i == y) {
                    it->setHP();
                    if (it->checkSunk()  == true) {
                        ShipNo--;
                    }
                }
            }
        }
    }
}

std::array<int,2> GameBoard::easyAIshoot() {
    int gr = 0;
    static int count=0;
    static std::array<int,2> lastMove, shot;
    static std::vector<std::array<int,2> > tmp(100,{0,0});
    std::srand(static_cast<unsigned int>(std::time(0)));

    if (count == 0) {
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++){
                tmp[i*10+j] = {i,j};
            }
        }
    }

    gr = tmp.size();
    int random = getNumber(0, gr);
    shot = {tmp[random][0], tmp[random][1]};
    int check = checkHit(tmp[random][0], tmp[random][1]);

    if (static_cast<status> (check) == hit) {
        lastMove = tmp[random];
    }

    tmp.erase(tmp.begin()+random);
    count ++;

    return shot;
}

std::array<int,2> GameBoard::AIshoot() {
    int gr = 0, check = 0;
    static int count=0;
    std::array<int,2> shot;
    static std::array<int,2> lastMove;
    static std::vector<std::array<int,2> > tmp(100,{0,0});
    std::srand(static_cast<unsigned int>(std::time(0)));

    if (count == 0) {
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++){
                tmp[i*10+j] = {i,j};
            }
        }
    }

    gr = tmp.size();

    int random = getNumber(0, gr);

    if (static_cast<status>(getGrid(lastMove[0],lastMove[1])) == hit) {
        for (int i=0; i<gr; i++) {
            if (abs(tmp[i][0] - lastMove[0]) < 2 && abs(tmp[i][1]-lastMove[1]) < 2) {
                check = checkHit(tmp[i][0], tmp[i][1]);
                shot = {tmp[i][0], tmp[i][1]};
                goto Nomatch;
            }
        }
        check = checkHit(tmp[random][0], tmp[random][1]);
        shot = {tmp[random][0], tmp[random][1]};
    } else {
        check = checkHit(tmp[random][0], tmp[random][1]);
        shot = {tmp[random][0], tmp[random][1]};
    }

Nomatch:
    if (static_cast<status> (check) == hit) {
        lastMove = shot;
    }

    for (int i=0; i<gr; i++) {
        if (tmp[i] == shot) tmp.erase(tmp.begin()+i);
    }

    count ++;

    return shot;
}

bool GameBoard::isGameOver() {
    if(ShipNo == 0) return true;
    else return false;
}

int GameBoard::getShipNo() const {
    return ShipNo;
}


int GameBoard::getCarNo() const {
    return CarNo;
}

int GameBoard::getCruNo() const {
    return CruNo;
}

int GameBoard::getDesNo() const {
    return DesNo;
}

int GameBoard::getSubNo() const {
    return SubNo;
}

int GameBoard::getGrid(int x, int y) const {
    return static_cast<int>(grid[x][y]);
}

int GameBoard::getPlaceSize() const {
    return PlaceSize;
}

GameBoard::Ship::Ship(shipsize s, int x, int y, int dir): size(s), sunk(false), HP(static_cast<int>(size)),
stPtx(x), stPty(y), dir(dir)
{
}

int GameBoard::Ship::getHP() const {
    return HP;
}

int GameBoard::Ship::getSize() const{
    return static_cast<int>(size);
}

bool GameBoard::Ship::checkSunk() const {
    return sunk;
}

void GameBoard::Ship::setSunk() {
    sunk = true;
}

void GameBoard::Ship::setHP() {
    if(HP > 1) {
        HP -= 1;
    }

    else if(HP == 1) {
        HP = 0;
        setSunk();
    }
}

int GameBoard::Ship::LocationStPtx() const {
    return stPtx;
}

int GameBoard::Ship::LocationStPty() const {
    return stPty;
}

int GameBoard::Ship::getDir() const {
    return dir;
}

int GameBoard::getNumber(int min, int max) {
    int randomNumber = std::rand()%(max - min) + min;
    return randomNumber;
}
