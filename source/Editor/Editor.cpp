#include "../../include/Editor/Editor.h"
#include <ncurses.h>


void Editor::loop(Cursor* cursor, int ch)
{
    cursor->draw();
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    if(ch == 'q' || ch == 'Q')
	return;
	
    for(;;){
	timeout(0);
    	ch = getch();
	
	cursor->erase();
	cursor->newCoordinates(ch);
	cursor->draw();
	move(0, 0);
	refresh();
	
	if(ch == 'q' || ch == 'Q')
	    break;
	
    }
}

void Editor::start(int ch)
{
    Cursor cursor(5,5);

    cursor.draw();
    move(0, 0);
    ch = getch(); // wait for pressing any key (in oder to not start imidiatly)
    if(ch == 'q' || ch == 'Q')
	return;
	
    for(;;){
	timeout(0);
    	ch = getch();
	
	cursor.erase();
	cursor.newCoordinates(ch);
	cursor.draw();
	move(0, 0);
	refresh();
	
//	if(cursor.mode==Cursor::Mode::draw){
//	    
//	}
	
	if(ch == 'd'){
	    cursor.changeMode(Cursor::Mode::draw);
	}
	
	else if(ch == 'e'){
	    cursor.changeMode(Cursor::Mode::erase);
	}
	
	else if(ch == 's'){
	    cursor.changeMode(Cursor::Mode::standBy);
	}
	else if (ch == 'q' || ch == 'Q')
	    break;
	
	else{
	}
    }
}