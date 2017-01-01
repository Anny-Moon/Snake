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
    
    printw("Press any key to start.\nIf you want to quit press \"q\" or \"Q\" at any time");
    attron(COLOR_PAIR(10));
    attron(A_BLINK);
    printw("\n\n\nLatest New!\n");
    attroff(COLOR_PAIR(10));
    attroff(A_BLINK);
    
    printw("Press\"1\" for game with bonuses");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();

    // Create all objects for game
    Box box(50, 30 ,5,5);
    Snake snake(5, 20, 30, 20000);
    RunningApple apple(&box,'$');
    apple.x = 30.0;
    apple.y = 30.0;
    Score score(5 ,3);
    Speed speed(35,3);
    
    // Starting Game loop
    Gameplay::gameLoop(&snake, &apple, &box, &score, &speed, ch);

    // Clear ncurses data structures (don't remove thus!)
    endwin();
    printf("Fin!\n");
    return 0;
}
