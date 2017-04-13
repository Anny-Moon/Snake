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
* @file Score.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Score.h"
#include <ncurses.h>

Score::Score(int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    points = 0;
    
}

Score::~Score(){}

void Score::calculatePoints(const Apple& apple)
{
    switch (apple.type){
	case Apple::normal:
	    points += 10;
	break;
	default:
	    points +=10;
	break;
    }
}

void Score::calculatePoints(int points_in)
{
    points += points_in;
}

void Score::draw() const
{
    mvprintw(y, x, "Score: %i",points);
}

