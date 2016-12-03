/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include <stdio.h>
#include <ncurses.h>

void Gameplay::gameLoop(Snake* snake, int ch)
{
    //char ch;
    ArrowKey key;
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen
    snake->draw();
    refresh();
 
    for(;;){
	ch = getch();

	if(ch == KEY_LEFT)
	    key = ArrowKey::left;
	
	else if (ch == KEY_RIGHT)
	    key = ArrowKey::right;
	
	else if (ch == KEY_UP)
	    key = ArrowKey::up;
	    
	else if (ch == KEY_DOWN)
	    key = ArrowKey::down;
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	else;
	snake->newCoordinates(key);
	erase();
	snake->draw();
	refresh();
    }
    
}