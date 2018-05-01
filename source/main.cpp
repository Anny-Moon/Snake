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
* @file main.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Snake.h"
#include "../include/Apple.h"
#include "../include/RunningApple.h"
#include "../include/Box.h"
#include "../include/Obstacle.h"
#include "../include/Score.h"
#include "../include/Speed.h"
#include "../include/Gameplay.h"
#include "../include/Piece.h"
#include "../include/Explosion.h"
#include "../include/Level.h"
#include "../include/Util.h"

#include "../include/Editor/Editor.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int main()
{	
    Util::createDir(PATH_TO_DIR_STR);
    if(Util::isFirstRun){
	for(int i=0;i<Util::levelDefault.size();i++)
	    Util::createDefaultLevelFile(i);
    }
    
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color(); 
    srand (time(NULL));

    // snakes
    init_pair(1, COLOR_BLUE, COLOR_CYAN);//snake1
    init_pair(2, COLOR_RED, COLOR_YELLOW);//snake2 (if allowed)
    
    //apples
    init_pair(3, COLOR_WHITE, COLOR_RED);//apples
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);//bonus (if allowed)
    
    //text
    init_pair(10,COLOR_RED,0);
    init_pair(11,COLOR_CYAN,0);
    init_pair(12,COLOR_BLUE,0);
    init_pair(13,COLOR_BLACK,COLOR_WHITE);
    
    
    bool exitFlag = 0;
    int ch;
    while(!exitFlag){
	// Clear the screen
	clear();
	attron(COLOR_PAIR(11));
	attron(A_DIM);
	mvprintw(1, 2,"Game");
	attroff(COLOR_PAIR(11));
	attroff(A_DIM);
	Gameplay::printLogo(2 ,3);
	attron(COLOR_PAIR(11));
	attron(A_DIM);
	mvprintw(7, 15,"by Anna Sinelnikova");
	attroff(COLOR_PAIR(11));
	attroff(A_DIM);
	mvprintw(11, 2, "Whenever you want to quit the game press 'q'.");
	attron(A_BLINK);
	attron(COLOR_PAIR(10));
	mvprintw(13, 2, "New!");
	mvprintw(14, 5, "Level editor! press 'e'");
	attroff(A_BLINK);
	attroff(COLOR_PAIR(10));
	mvprintw(16, 2, "Press 'r' for random map level.");
	
	mvprintw(17, 2, "Press 'l' to load the previous saved level you created in the editor.");
	
	mvprintw(18, 2, "Press '0' for classical game.");
	
	mvprintw(19, 2, "Press '1', '2' or '3' to play our prebuilt levels.");
	
	mvprintw(21, 2, "When you play you can pause/resume the game with 'p' button.");
	mvprintw(22, 2, "You can adjust speed (not in classical game) by pressing '=/+' or '-'.");
	
	move(0,0);
    
	//Wait until the user press a key
	timeout(-1);
	ch = getch();
 
	// Clear the screen
	clear();
//Cursor cursor(5,5);
	// Starting Game loop
	switch(ch){
	    case '1':
		//Level::one(ch);
		Level::levelTemplate(ch, "_level1.dat");
		break;
	    case '2':
		//Level::two(ch);
		Level::levelTemplate(ch, "_level2.dat");
		break;
	    case '3':
		//Level::three(ch);
		Level::levelTemplate(ch, "_level3.dat");
		break;
	    case 'r':
		Level::random(ch);
		break;
	    case 'l':
		Level::levelTemplate(ch, "level.dat");
		break;
	    case 'e':
		Editor::start(ch);
		//Editor::loop(&cursor, ch);
		break;
	    case 'Q':
	    case 'q':
		exitFlag = 1;
		break;
	    default:
		Level::zero(ch);
		break;
	}
    }
    // Clear ncurses data structures (don't remove thus!)
    endwin();
    printf("\t\tThank you for the game!\n");
    return 0;
}
