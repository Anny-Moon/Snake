#pragma once
#include "../../include/Editor/Cursor.h"
#include <ncurses.h>

class Editor{
    
public:
    void static loop(Cursor* cursor, int ch);
    void static start(int ch);
};