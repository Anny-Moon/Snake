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
* @file Speed.h
* @autor Anna Sinelnikova
* @data 2016
*/

#ifndef SNAKE_SPEED
#define SNAKE_SPEED

#include <ncurses.h>

class Speed
{
private:
public:
    int points;
    int x;
    int y;
    
    Speed(int x_in, int y_in);
    ~Speed();
    
    void calculatePoints(int points_in);
    void draw() const;
};

#endif