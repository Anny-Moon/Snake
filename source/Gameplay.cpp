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
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen
    snake->draw();
    refresh();
 
    for(;;){
	ch = getch();

	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN){
	    snake->newCoordinates(ch);
	    erase();
	    snake->draw();
	    refresh();
	}
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	
    }
    
}