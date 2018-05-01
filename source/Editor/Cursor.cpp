/* Copyright 2018 Anna Sinelnikova
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
* @file Cursor.cpp
* @autor Anna Sinelnikova
* @data 2018
*/

#include "../../include/Editor/Cursor.h"
#include "../../include/Box.h"
#include <ncurses.h>

Cursor::Cursor(int xStart, int yStart)
{
    x = xStart;
    y = yStart;
    symbol = 'o';
    mode = Mode::standBy;
    color = 1;
}

Cursor::~Cursor(){};

void Cursor::draw() const
{
    attron(COLOR_PAIR(color));
    mvaddch(y, x, symbol);
    attroff(COLOR_PAIR(color));
}

void Cursor::erase() const
{
    mvaddch(y, x, ' ');
}

void Cursor::newCoordinates(int arrowKey, const Box& box)
{
    switch (arrowKey){
    	case KEY_LEFT:
    	    if(x>box.left)
		x = x - 1;
	    else{
		if(box.boundryConditions==1)
		    x = box.right;
	    }
	break;
	
	case KEY_RIGHT:
	    if(x<box.right)
		x = x + 1;
	    else{
		if(box.boundryConditions==1)
		    x = box.left;
	    }
	break;
	
	case KEY_UP:
	    if(y>box.top)
		y = y - 1;
	    else{
		if(box.boundryConditions==1)
		    y = box.bottom;
	    }
	break;
	
	case KEY_DOWN:
	    if(y<box.bottom)
		y = y + 1;
	    else{
		if(box.boundryConditions==1)
		    y = box.top;
	    }
	break;
	default:
	break;
    }// end of case
}

void Cursor::changeMode(Mode newMode){
    if(newMode == mode)
	return;
	
    else{
	mode = newMode;
	
	switch(mode){
	    case Mode::standBy:
		color = 1;
	    break;
	    case Mode::draw:
		color = 2;
	    break;
	    case Mode::erase:
		color = 3;
	    break;
	    default:
	    break;
	}
    }
}