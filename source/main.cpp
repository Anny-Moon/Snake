/** @package Snake
* @file main.cpp
* @autor Anna Sinelnikova
* @data 2016
*/

#include "../include/Snake.h"
#include "../include/Apple.h"
#include "../include/Box.h"
#include "../include/Score.h"
#include "../include/Gameplay.h"
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
    //beep();
    start_color(); 
    srand (time(NULL));
    
    init_color(COLOR_BLUE, 0, 700, 900);
    init_pair(1, COLOR_BLUE, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    printw("Press any key to start.\nIf you want to quit press \"q\" or \"Q\" at any time");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();
    Box box(50, 30 ,5,5);
    Snake snake(4, 20, 30);
    Apple apple(30, 30, '$');
    Score score(5 ,3);
    // Start the game loop
    Gameplay::gameLoop(&snake, &apple, &box, &score, ch);
    // Clear ncurses data structures
    endwin();
    printf("Fin!\n");
    return 0;
}
