#include "../Box.h"
#pragma once

class Cursor{
private:
    char symbol;
    int color;
    
public:
    int x;
    int y;
    
    enum class Mode{standBy, draw, erase} mode;
    
    Cursor(int xStart, int yStart);
    ~Cursor();
    
    void draw() const;
    void erase() const;
    void newCoordinates(int arrowKey, const Box& box);
    void changeMode(Mode newMode);
    
    inline void setX(int value);
    inline void setY(int value);

};

inline void Cursor::setX(int value){
    x = value;
}

inline void Cursor::setY(int value){
    y = value;
}