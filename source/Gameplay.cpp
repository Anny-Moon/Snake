/** @package Snake
* @file Gameplay.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Gameplay.h"
#include <ncurses.h>
//#include <time.h>
int Gameplay::kbhit()
{
    int ch = getch();
    printw("%i\n", ch);
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } 
    
    else {
        return 0;
    }

}

void Gameplay::gameLoop(Snake* snake, int ch)
{
//    time_t initialTime, currentTime;
    int latestCh = ch;
    
    if(ch == 'q' || ch == 'Q')
	return;
    
    // Show the main character on the screen
    snake->draw();
    refresh();
    
    for(;;){
//	initialTime = time(NULL);
//	currentTime = time(NULL);
	
	timeout(0);
    	ch = getch();
	    
	if(ch == ERR)
	    ch = latestCh;
	//if(kbhit()){
	//	ch = getch();
	//    }
	//ch = latestCh;
	//timeout(200);
	//else
	//    ch = latestCh;
	
	//printw("%.f\n",difftime(time(NULL),initialTime));
	//refresh();
	//if(difftime(time(NULL),initialTime)>0.5){
	//    ch = KEY_UP;}
	
	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN){
	    snake->newCoordinates(ch);
	    erase();
	    snake->draw();
	    refresh();
	}
	
	else if(ch == 'q' || ch == 'Q')
	    break;
	latestCh = ch;
	
	//pause 
	napms(500);
    }
    
}