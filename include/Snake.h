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
* @file Snake.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef ANNA_SNAKE
#define ANNA_SNAKE

#include "Apple.h"
#include "Box.h"
#include "Obstacle.h" //for collosionDetection with obstacles

class Snake
{
private:
    char headChar;
    char bodyChar;
    
public:
    int length;
    int* x;
    int* y;
    
    int dTime;//< delay in msec
    
    int keyboardMode;//< for multiplayer
    int colorScheme;
    
    Snake(int length_in = 5, int xSatrt = 10, int yStart = 10, int dTime_in = 100);///@param x, y - position of head
    ~Snake();
    
    void erase() const;
    void draw() const;
    void newCoordinates (int arrowKey);
    bool collisionDetection(const Box& box);
    bool collisionDetection(const Obstacle* obstacle, int N);//<collision with obtacles;
    int headDirection();
    int tailDirection();
    void changeLength(int newLength);
    void eatApple(Apple::Type appleType);
};

#endif