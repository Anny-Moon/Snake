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
    init_color(COLOR_BLUE, 0, 700, 900);
    init_pair(1, COLOR_BLUE, COLOR_CYAN
    );
    
    printw("Do you want to play a bit ;)\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();
    Snake snake(15, 20, 10);
    // Start the game loop
    attron(COLOR_PAIR(1));
    Gameplay::gameLoop(&snake, ch);
    attroff(COLOR_PAIR(1));
    // Clear ncurses data structures
    endwin();
    printf("Fin!\n");
    return 0;
}
