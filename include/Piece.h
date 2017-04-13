/* Copyright 2017 Anna Sinelnikova
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/

/** @package Snake
* @file Piece.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_PIECE
#define ANNA_PIECE

#include "Box.h"
#include "Obstacle.h"

class Piece
{
private:
    
public:
    char pieceChar;
    int colorScheme;
    
    double x;
    double y;
    
    int intX;
    int intY;
    
    double velocityX;
    double velocityY;
    
    double accelerationX;
    double accelerationY;
    
    double time;
    const Box* box;
    
    int numObstacles;
    const Obstacle* obstacle; //array of obstacles
    
    Piece(double x0, double y0, double vx0, double vy0, double ax0 = 0.0, double ay0 = 0.0, const Box* box_in = NULL, double time0 = 0.0);
    Piece();
    ~Piece();
    
    void setBox(const Box* box);
    void setObstacles(const Obstacle* obst, int numObst);
    
    int rounding(double number);
    int findIntX();
    int findIntY();
    void findCoordinates(double time, const int* xObst = NULL, const int* yObst = NULL, int N=0);//< arrays of odstacle coordinates
    void erase() const;
    void draw() const;
};

#endif