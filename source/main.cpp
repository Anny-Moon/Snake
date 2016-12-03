#include "../include/Snake.h"
#include "../include/Gameplay.h"
#include <ncurses.h>

int main()
{
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    //beep();
    start_color(); 
    
    printw("Do you want to play a bit ;)\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();
    Snake snake(15, 20, 10);
    // Start the game loop
    Gameplay::gameLoop(&snake, ch);
    
    // Clear ncurses data structures
    endwin();
    printf("Fin!\n");
    return 0;
}
