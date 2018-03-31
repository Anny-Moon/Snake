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

#include "../include/Editor/Editor.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include <string> // required for std::string
#include <sys/types.h> // required for stat.h
#include <sys/stat.h>

#include "../include/Global.h"
int main()
{	
    //create or chech if directory exist
    bool isDirExists=false;
    int nError = 0;
    mode_t nMode = 0733; // UNIX style permissions
    
    struct stat st;
    if(stat(PATH_TO_DIR,&st) == 0){
	if(st.st_mode & S_IFDIR != 0){
//	    printf("exist\n");
	    isDirExists = true;
	}
    }
    else{
//	printf("NOT exist\n");
	isDirExists = false;
    }
    
    if(!isDirExists){
	printf("I created the directory: '%s'.\n", PATH_TO_DIR);
	printf("It will be used for the game files.\n", PATH_TO_DIR);
	nError = mkdir(PATH_TO_DIR, nMode);
    }
    
    if (nError != 0) {
	printf("Error:\n\tcannot create dir '%s'.\n",PATH_TO_DIR);
	exit(1);
    }

    ////////////////////////////////////
    
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
	mvprintw(10, 2, "Press any key to start.");
	mvprintw(11, 2, "When you want to quit press 'q' or 'Q'.");
	attron(A_BLINK);
	attron(COLOR_PAIR(10));
	mvprintw(13, 2, "New!");
	mvprintw(13, 10, "Try level 4!");
	attroff(A_BLINK);
	attroff(COLOR_PAIR(10));
	mvprintw(14, 2, "If you do not like it, press 'q' and then try again!");
	mvprintw(16, 2, "You can adjust speed(not in classical game) by pushing '=' or '-'.");
	mvprintw(17, 2, "Choose the level '1', '2', '3' or '4'.");
	mvprintw(18, 2, "Or press any button for classical game.");
	
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
		Level::one(ch);
		break;
	    case '2':
		Level::two(ch);
		break;
	    case '3':
		Level::three(ch);
		break;
	    case '4':
		Level::four(ch);
		break;
	    case 't':
		Level::levelTemplate(ch);
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
	//if(ch == '1')
	//    Level::one(ch);
	
	//else if(ch == '2')
	//    Level::two(ch);
	
	//else if(ch == '3')
	//    Level::three(ch);
	
	//else if(ch == 'Q' || ch == 'q')
	//    break;
	
	//else
	//    Level::zero(ch);
	}
    }
    // Clear ncurses data structures (don't remove thus!)
    endwin();
//    printf("It was a good game!\n");
    printf("\t\tThank you for the game!\n");
    return 0;
}
