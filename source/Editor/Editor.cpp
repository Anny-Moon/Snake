#include "../../include/Editor/Editor.h"
#include "../../include/Obstacle.h"

#include "../../include/Gameplay.h"
#include "../../include/Level.h"
#include "../../include/Global.h"

#include <ncurses.h>
#include <vector>
#include <string>

void Editor::boxRescale(int ch, Box* box){
    char a[4];
    a[0] = ch;
    int count = 1;
    for(;;){
	timeout(0);
	ch = getch();
	
	if(_IS_NUMBER(ch)){
	    a[count] = ch;
    	    count++;
	}
	
	_QUITE(ch);
	
	if(count==4){
	    break;
	}
    }
    
    char a0 = a[0];
    char a1 = a[1];
    char a2 = a[2];
    char a3 = a[3];
    
    char chOne = '1';
    int one=(int)chOne;
    
    int b0=int(a0) - one+1;
    int b1=int(a1) - one+1;
    int b2=int(a2) - one+1;
    int b3=int(a3) - one+1;
    
//    mvprintw(15,80,"%d, %d, %d, %d", b0, b1, b2, b3);
    int width, height;
    width = b0*10+b1;
    height = b2*10+b3;
    
    mvprintw(20,80,"%i", width);
    mvprintw(22,80,"%i", height);
    
    box->erase(); //erase the old box;
    box->setWidth(width);
    box->setHeight(height);
//    box->draw();
}

void Editor::start(int ch)
{	
    std::string levelName;
    FILE* fp;
    bool flagPlay = false;
    Cursor cursor(10,10);
    Box box(35, 15 ,5, 5, 1);
    std::vector<Obstacle> obstacle;
    Obstacle* tmpObst;
    cursor.draw();
    box.draw();
    
//    Gameplay::printLogo(box.bottom+2,box.left+10);
    attron(COLOR_PAIR(11));
    attron(A_DIM);
    mvprintw(0,box.left,"(c) Anna Sinelnikova");
    attroff(COLOR_PAIR(11));
    attroff(A_DIM);
    
    
    mvprintw(2,box.left,"EDIT MODE");
    
    mvprintw(1,box.left+10,"'d' - for draw");
    mvprintw(2,box.left+10,"'e' - for erase");
    mvprintw(3,box.left+10,"'w' - for stand by");
    
    mvprintw(1,box.left+30,"'b' - for changing boundry conditions");
    mvprintw(2,box.left+30,"'s' - to save");
    mvprintw(3,box.left+30,"'p' - for instant play");
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
	
	else if(ch == 'w'){
	    cursor.changeMode(Cursor::Mode::standBy);
	}
	
	else if(ch == 'b'){
	    box.boundryConditions = (box.boundryConditions+1)%2;
	    box.draw();
	}
	
	else if (ch == 'q' || ch == 'Q')
	    break;
	
	else if (ch == 's'){
	    levelName = PATH_TO_DIR_STR + "/level.dat";
	    fp=fopen(levelName.c_str(),"w");
	    fprintf(fp,"generated in Level Editor\n");
	    box.writeInFile(fp);
	    Obstacle::writeInFile(fp, obstacle);
	    fclose(fp);
	}
	
	else if (ch == 'p'){
	    levelName = PATH_TO_DIR_STR + "/leve.dat";
	    fp=fopen(levelName.c_str(),"w");
	    fprintf(fp,"generated in Level Editor\n");
	    box.writeInFile(fp);
	    Obstacle::writeInFile(fp, obstacle);
	    fclose(fp);
	    flagPlay = true;
	    break;
	}
	
	//rescale the box
	
	else if(_IS_NUMBER(ch)){
	    boxRescale(ch, &box);
	//    box.erase();
	    box.draw();
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