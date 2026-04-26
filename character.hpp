//Authors: CB, SH, YG, LP, 
#pragma once
#include <SFML/Graphics.hpp>
class Character
{
protected:
int row, col;

public:
Character(int r, int c) : row(r), col(c) {}

virtual void draw(sf::RenderWindow& window) = 0;

int getRow() { return row; }
int getCol() { return col; }

void setPosition(int r, int c)
{
row = r;
col = c;
}
};
