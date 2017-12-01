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
    void newCoordinates(int arrowKey);
    void changeMode(Mode newMode);

};