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
* @file Level.h
* @autor Anna Sinelnikova
* @data 2017
*/

#ifndef SNAKE_LEVEL
#define SNAKE_LEVEL

#include "Gameplay.h"

#define _QUITE(ch) if(ch == 'q' || ch == 'Q') return;

#define _PAUSE(ch) if(ch == 'p' || ch == 'P'){\
		    for(;;){\
			attron(COLOR_PAIR(10));\
			attron(A_BLINK);\
			mvprintw(3, 21,"PAUSED");\
			attroff(A_BLINK);\
			attroff(COLOR_PAIR(10));\
			move(0,0);\
			timeout(-1);\
    			ch = getch();\
    			_QUITE(ch);\
    			if(ch == 'p' || ch == 'P'){\
    			    ch = '1';\
			    mvprintw(3, 21,"      ");\
    			    break;\
    			}\
    		    }\
    		}

class Level
{
private:
    class Drawable{
    public:
	Box* box;
	Obstacle* obstacle;
	int numObst;
//	Snake snake;
//	RunningApple apple;
//	Score score;
//	Speed speed;
	
	Drawable(const char* fileName);
	~Drawable();
	
    };
public:
    
    static void zero(int ch); //< classical
    static void random(int ch);
    static void levelTemplate(int ch, const std::string fileName);

};

#endif