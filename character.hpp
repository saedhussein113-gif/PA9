//Authors: CB, SH, YG, LF, KT
//Project: Programming Assingment 9
//Description: Pac-Man
//Date: 4/26/26
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
