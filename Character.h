/* Authors: CB, SH, YG, LF
* Course : CPTS 122
* Assignment : Programming Assignment 9
* Project : Pac - Man
*
*File : character.h
*
*Description :
*Base Character class used that is gonna be used as the parent for all the game entities
* this Handles position tracking and implementation of a draw function.
*
* Date : April 23, 2026
*/

#pragma once
#include <SFML/Graphics.hpp>
//class for characters, parent class for player and ghosts
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