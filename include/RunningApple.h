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
* @file RunningApple.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_RUNNING_APPLE
#define ANNA_RUNNING_APPLE

#include "Box.h"
#include "Obstacle.h"
#include "Piece.h"

class RunningApple : public Piece
{
private:
public:
    
    enum Type{normal, money};//< different bonuses
    Type type;
    int cost;
    
    RunningApple(const Box* box_in, char ch = '#', Type type_in = normal, const Obstacle *obst = NULL, int numObst = 0);
    ~RunningApple();
    void move(int intX_in, int intY_in);
    
    void newStableApple();
    void newRunningApple(double time0, int maxXspeed = 20000, int maxYspeed = 20000);
    void setAsBonus(Type type);
    bool eatingDetection(int xSnake, int ySnake);
};

#endif