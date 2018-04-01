#pragma once
#include "../../include/Editor/Cursor.h"
#include "../../include/Box.h"

#include <ncurses.h>


#define _IS_NUMBER(ch)\
    ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'
    
class Editor{
    
public:
    void static loop(Cursor* cursor, int ch);
    void static boxRescale(int ch, Box* box);
    void static start(int ch);
};