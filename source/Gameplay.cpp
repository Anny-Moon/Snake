/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include <ncurses.h>
#include <time.h>

void Gameplay::gameLoop(Snake* snake, int ch)
{
    time_t initialTime, currentTime;
    int latestCh = ch;
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen
    snake->draw();
    refresh();
    
    for(;;){
	initialTime = time(NULL);
	currentTime = time(NULL);
	
	timeout(0);
    	ch = getch();
	    
	//while(difftime(currentTime,initialTime)<0.5){
	//    currentTime = time(NULL);
	//    if(ch != ERR)
	//	break;
	//}
	
	if(ch == ERR)
	    ch = latestCh;
	
	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN){
	    snake->newCoordinates(ch);
	    erase();
	    snake->draw();
	    refresh();
	}
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	
	if(snake->collisionDetection())
	{	
	    beep();
	    clear();
	    attron(COLOR_PAIR(2));
	    printw("LOOOOOSER!\n");
	    refresh();
	    napms(2000);
	    return;
	}
	
	latestCh = ch;
	//pause 
	napms(300);
    }
    
}