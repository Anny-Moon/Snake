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
* @file Explosion.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_EXPLOSION
#define ANNA_EXPLOSION

#include "Box.h"
#include "Piece.h"

class Explosion
{
private:
    int numPieces;
    Piece* piece;
    double time;
public:
    int* x;
    int* y;
    const Box* box;
    
    double* velocityX;
    double* velocityY;
    double* accelerationX;
    double* accelerationY;
    
    Explosion(int numPieces_in, const int* x_in, const int* y_in, const Box* box_in, double time0 = 0.0);
    ~Explosion();
    
    void setPhysics(); //< set velocities and accelerations
    void findCoordinates(double time_in, const int* xObst, const int* yObst, int N);
        
    void erase() const;
    void draw() const;
};

#endif