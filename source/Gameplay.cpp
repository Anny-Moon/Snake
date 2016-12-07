/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include <ncurses.h>
#include <time.h>

void Gameplay::gameLoop(Snake* snake, Apple* apple, Box* box, int ch)
{
    time_t initialTime, currentTime;
    int latestCh = ch;
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen
    box->draw();
    snake->draw();
    apple->draw();
    
    refresh();
    
    for(;;){
//	initialTime = time(NULL);
//	currentTime = time(NULL);
	
	if(apple->collisionDetection(snake->x[0], snake->y[0])){
	    snake->eatApple(Apple::normal);
	    apple->newCoordinates(*box);
	    erase();
	    box->draw();
	    apple->draw();
	    snake->draw();
	    move(0, 0);// move cursor
	    refresh();
	}
	
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
	    box->draw();
	    apple->draw();
	    snake->draw();
	    move(0, 0); // move cursor
	    refresh();
	}
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	
	if(snake->collisionDetection(*box))
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
	napms(100);
    }
    
}