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
* @file Speed.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Speed.h"
#include <ncurses.h>

Speed::Speed(int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    points = 1;
    
}

Speed::~Speed(){}


void Speed::calculatePoints(int points_in)
{
    points += points_in;
}

void Speed::draw() const
{
    mvprintw(y, x, "Speed: %i",points);
}

