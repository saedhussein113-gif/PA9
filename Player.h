/*
 * Authors: CB, SH, YG, LF
 * Course: CPTS 122
 * Assignment: Programming Assignment 9
 * Project: Pac-Man
 *
 * File: Player.h
 *
 * Description:
 * This file defines the Player class, the user-controlled character 
 * in the Pac-Man game. The Player class inherits from the Character 
 * base class and implements its own rendering logic using SFML.
 *
 * Features:
 * - Inherits position handling from Character class
 * - Renders player 
 * - Integrates with game movement and collision system
 *
 * Date: April 23, 2026
 */
#pragma once
#include "Character.h"
//class for player character, inherits from character class
class Player : public Character
{
public:
    Player(int r, int c) : Character(r, c) {}

    void draw(sf::RenderWindow& window) override
    {
        sf::CircleShape shape(16);
        shape.setPosition(sf::Vector2f(col * 32, row * 32));
        shape.setFillColor(sf::Color::Yellow);
        window.draw(shape);
    }  
};