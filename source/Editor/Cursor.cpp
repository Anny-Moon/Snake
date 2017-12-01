#include "../../include/Editor/Cursor.h"
#include <ncurses.h>

Cursor::Cursor(int xStart, int yStart)
{
    x = xStart;
    y = yStart;
    symbol = 'o';
    mode = Mode::standBy;
    color = 1;
}

Cursor::~Cursor(){};

void Cursor::draw() const
{
    attron(COLOR_PAIR(color));
    mvaddch(y, x, symbol);
    attroff(COLOR_PAIR(color));
}

void Cursor::erase() const
{
    mvaddch(y, x, ' ');
}

void Cursor::newCoordinates(int arrowKey)
{
    int i;
    switch (arrowKey){
    	case KEY_LEFT:
	    x = x - 1;
	break;
	
	case KEY_RIGHT:
	    x = x + 1;
	break;
	
	case KEY_UP:
	    y = y - 1;
	break;
	
	case KEY_DOWN:
	    y = y + 1;
	break;
	default:
	break;
    }// end of case
}
