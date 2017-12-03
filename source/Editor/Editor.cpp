#include "../../include/Editor/Editor.h"
#include "../../include/Obstacle.h"

#include "../../include/Gameplay.h"
#include "../../include/Level.h"

#include <ncurses.h>
#include <vector>



void Editor::start(int ch)
{
    FILE* fp;
    bool flagPlay = false;
    Cursor cursor(10,10);
    Box box(35, 15 ,5, 5, 1);
    std::vector<Obstacle> obstacle;
    Obstacle* tmpObst;
    cursor.draw();
    box.draw();
    
    Gameplay::printLogo(box.bottom+2,box.left+10);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    
    mvprintw(2,box.left,"EDIT MODE");
    
    mvprintw(1,box.left+10,"'d' - for draw");
    mvprintw(2,box.left+10,"'e' - for erase");
    mvprintw(3,box.left+10,"'s' - for stand by");
    
    mvprintw(1,box.left+30,"'b' - for changing boundry conditions");
    mvprintw(2,box.left+30,"'p' - for instant play");
    
    move(0, 0);
	
    for(;;){
	timeout(0);
    	ch = getch();
	
	if(ch == 'd'){
	    cursor.changeMode(Cursor::Mode::draw);
	}
	
	else if(ch == 'e'){
	    cursor.changeMode(Cursor::Mode::erase);
	}
	
	else if(ch == 's'){
	    cursor.changeMode(Cursor::Mode::standBy);
	}
	
	else if(ch == 'b'){
	    box.boundryConditions = (box.boundryConditions+1)%2;
	    box.draw();
	}
	
	else if (ch == 'q' || ch == 'Q')
	    break;
	
	else if (ch == 'p'){
	    fp=fopen("level.dat","w");
	    fprintf(fp,"generated in Level Editor\n");
	    box.writeInFile(fp);
	    Obstacle::writeInFile(fp, obstacle);
	    fclose(fp);
	    flagPlay = true;
	    break;
	}
	
	else{
	}
	
	for(int k=0;k<obstacle.size();k++){
	    obstacle[k].draw();
	}
	
	cursor.erase();
	cursor.newCoordinates(ch, box);
	cursor.draw();
	move(0, 0);
	refresh();
	
	if(cursor.mode==Cursor::Mode::draw){
	    if(Obstacle::isPixelFree(cursor.x, cursor.y, obstacle)){
		tmpObst = new Obstacle();
		tmpObst->init(1, 1, cursor.x, cursor.y);
		obstacle.push_back(*tmpObst);
		delete tmpObst;
	    }
	}
	
	else if(cursor.mode==Cursor::Mode::erase){
	    for(int k=0;k<obstacle.size();k++){
		if(obstacle[k].x[0]==cursor.x && obstacle[k].y[0]==cursor.y){
		    obstacle.erase(obstacle.begin()+k);
		    break;
		}
	    }
	}
	
	else{};
	
	
    }
    
    if(flagPlay){
	timeout(-1);
//	ch = getch();
	Level::levelTemplate(ch);
    }
}