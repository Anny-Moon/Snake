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
    //beep();
    start_color(); 
    srand (time(NULL));
    
    init_color(COLOR_BLUE, 0, 700, 900);
    init_pair(1, COLOR_BLUE, COLOR_CYAN);
    init_pair(2, COLOR_RED, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    
    printw("Press any key to start.\nIf you want to quit press \"q\" or \"Q\" at any time");
    printw("\n\n\nNew: press\"2\" for 2 players");
    // Wait until the user press a key
    int ch = getch();
 
    // Clear the screen
    clear();
    Box box(50, 30 ,5,5);
    Snake snake(5, 20, 30, 100);
    RunningApple apple(&box,'$');
    apple.x = 30.0;
    apple.y = 30.0;

    Score score(5 ,3);
    
    Piece piece (10.0, 10.0, 0.02, 0.051, -0.000001, -0.00001, &box);
    // Start the game loop
    if (ch == '2'){
	Box box(60, 30 ,5,5);
	RunningApple apple(&box,'$');
	apple.x = 30.0;
	apple.y = 30.0;
	
	Snake snake(5, 20, 30, 100);
	Snake snake2(5, 20, 10, 100);
	snake2.keyboardMode = 2;
	snake2.colorScheme = 2;
	Score score2(30, 3);
	Gameplay::gameLoopForTwo(&snake, &snake2, &apple, &box, &score, &score2, ch);
    }
    
    else{
	Box box(50, 30 ,5,5);
	Snake snake(5, 20, 30, 100);
	RunningApple apple(&box,'$');
	apple.x = 30.0;
	apple.y = 30.0;
	Gameplay::gameLoop(&snake, &apple, &box, &score, ch);
    }
    // Clear ncurses data structures
    endwin();
    printf("Fin!\n");
    return 0;
}
