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
* @file Apple.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Apple.h"
#include <stdlib.h> // for random
#include <ncurses.h>

Apple::Apple(int x_in, int y_in, char ch, Type type_in)
{
    x = x_in;
    y = y_in;
    appleChar = ch;
    type = type_in;

}

Apple::~Apple(){}

void Apple::erase() const
{
    mvaddch(y, x, ' ');
}
void Apple::draw() const
{	
    attron(COLOR_PAIR(2));
    mvaddch(y, x, appleChar);
    attroff(COLOR_PAIR(2));
}

void Apple::newCoordinates(const Box& box)
{
    x = rand() % box.width + box.left;
    y = rand() % box.height + box.top;
}

bool Apple::collisionDetection(int xSnake, int ySnake)
{
    if(xSnake == x && ySnake == y)
	return true;
	
    return false;
}