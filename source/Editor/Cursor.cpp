#include "../../include/Editor/Cursor.h"
#include "../../include/Box.h"
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

void Cursor::newCoordinates(int arrowKey, const Box& box)
{
    switch (arrowKey){
    	case KEY_LEFT:
    	    if(x>box.left)
		x = x - 1;
	break;
	
	case KEY_RIGHT:
	    if(x<box.right)
		x = x + 1;
	break;
	
	case KEY_UP:
	    if(y>box.top)
		y = y - 1;
	break;
	
	case KEY_DOWN:
	    if(y<box.bottom)
		y = y + 1;
	break;
	default:
	break;
    }// end of case
}

void Cursor::changeMode(Mode newMode){
    if(newMode == mode)
	return;
	
    else{
	mode = newMode;
	
	switch(mode){
	    case Mode::standBy:
		color = 1;
	    break;
	    case Mode::draw:
		color = 2;
	    break;
	    case Mode::erase:
		color = 3;
	    break;
	    default:
	    break;
	}
    }
}