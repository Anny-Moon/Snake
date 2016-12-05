#include "../include/Snake.h"
#include "../include/Apple.h"
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
    printw("Do you want to play a bit ;)\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();
    Snake snake(4, 20, 30);
    Apple apple(30, 30, '$');
    // Start the game loop
    attron(COLOR_PAIR(1));
    Gameplay::gameLoop(&snake, &apple, ch);
    attroff(COLOR_PAIR(1));
    // Clear ncurses data structures
    endwin();
    printf("Fin!\n");
    return 0;
}
