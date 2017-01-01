/** @package Snake
* @file main.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Snake.h"
#include "../include/Apple.h"
#include "../include/RunningApple.h"
#include "../include/Box.h"
#include "../include/Score.h"
#include "../include/Speed.h"
#include "../include/Gameplay.h"
#include "../include/Piece.h"
#include "../include/Explosion.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

int main()
{
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
    init_pair(10,COLOR_RED,NULL);
    init_pair(11,COLOR_CYAN,NULL);
    
    
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
    move(0,0);
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();

    // Create all objects for game
    Box box(50, 30 ,5,5);
    Snake snake(5, 20, 30, 20000);
    RunningApple apple(&box,'Q');
    apple.x = 30.0;
    apple.intX = 30;
    apple.y = 30.0;
    apple.intY = 30;
    Score score(6 ,3);
    Speed speed(46 ,3);
    
    // Starting Game loop
    Gameplay::gameLoop(&snake, &apple, &box, &score, &speed, ch);

    // Clear ncurses data structures (don't remove thus!)
    endwin();
    printf("It was a good game!\n");
    return 0;
}
