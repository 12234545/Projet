#pragma once
//class pour avoir n'importe quelle  position 
class Position {
public:
//abscisse et ordonné
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }
};