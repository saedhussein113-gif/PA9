/*
 * Authors: CB, SH, YG, LF
 * Course: CPTS 122
 * Assignment: Programming Assignment 9
 * Project: Pac-Man
 *
 * File: Ghost.h
 *
 * Description:
 * This file defines the Ghost class hierarchy for the game.
 * The base Ghost class extends the Character class and gives
 * shared functionality. Three ghost types inherit from this class
 * each implementing unique movement behaviors:
 *
 * - ChaserGhost: Moves toward the player's current position
 *   using Manhattan distance.
 * - RandomGhost: Moves in random valid directions.
 * - AmbushGhost: Predicts the player's future position and
 *   attempts to intercept.
 *
 * Features:
 * - Abstract base class with movement behavior
 * - Tile-based movement with collision checking
 * - SFML rendering for ghost visuals
 * - Simple strategies for different ghost behaviors
 *
 * Date: April 23, 2026
 */
#pragma once
#include "Character.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

const int TILE = 32;
//class for ghost characters, abstract class with 3 different types of ghosts that inherit from it
class Ghost : public Character
{
protected:
    sf::Color color;

public:
    Ghost(int r, int c, sf::Color ghostColor)
        : Character(r, c), color(ghostColor) {
    }

    virtual void move(const std::vector<std::string>& map, int playerR, int playerC) = 0;

    bool canMove(const std::vector<std::string>& map, int r, int c)
    {
        return r >= 0 && r < map.size() &&
            c >= 0 && c < map[r].size() &&
            map[r][c] != '#';
    }

    void draw(sf::RenderWindow& window) override
    {
        sf::CircleShape body(14);
        body.setPosition(sf::Vector2f(col * TILE + 2, row * TILE + 2));
        body.setFillColor(color);
        window.draw(body);

        sf::CircleShape eye1(3);
        eye1.setPosition(sf::Vector2f(col * TILE + 8, row * TILE + 9));
        eye1.setFillColor(sf::Color::White);
        window.draw(eye1);

        sf::CircleShape eye2(3);
        eye2.setPosition(sf::Vector2f(col * TILE + 19, row * TILE + 9));
        eye2.setFillColor(sf::Color::White);
        window.draw(eye2);
    }
};
//class for chaser ghost, moves towards player
class ChaserGhost : public Ghost
{
public:
    ChaserGhost(int r, int c) : Ghost(r, c, sf::Color::Red) {}

    void move(const std::vector<std::string>& map, int playerR, int playerC) override
    {
        int bestR = row;
        int bestC = col;
        int bestDist = 9999;

        int dr[4] = { -1, 1, 0, 0 };
        int dc[4] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (canMove(map, nr, nc))
            {
                int dist = abs(playerR - nr) + abs(playerC - nc);

                if (dist < bestDist)
                {
                    bestDist = dist;
                    bestR = nr;
                    bestC = nc;
                }
            }
        }

        setPosition(bestR, bestC);
    }
};
//class for random ghost, moves randomly
class RandomGhost : public Ghost
{
public:
    RandomGhost(int r, int c) : Ghost(r, c, sf::Color(255, 105, 180)) {}

    void move(const std::vector<std::string>& map, int playerR, int playerC) override
    {
        int dr[4] = { -1, 1, 0, 0 };
        int dc[4] = { 0, 0, -1, 1 };

        for (int tries = 0; tries < 10; tries++)
        {
            int i = rand() % 4;
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (canMove(map, nr, nc))
            {
                setPosition(nr, nc);
                return;
            }
        }
    }
};
//class for ambush ghost, tries to move to where player will be in 2 turns
class AmbushGhost : public Ghost
{
public:
    AmbushGhost(int r, int c) : Ghost(r, c, sf::Color::Cyan) {}

    void move(const std::vector<std::string>& map, int playerR, int playerC) override
    {
        int targetR = playerR;
        int targetC = playerC + 2;

        int bestR = row;
        int bestC = col;
        int bestDist = 9999;

        int dr[4] = { -1, 1, 0, 0 };
        int dc[4] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (canMove(map, nr, nc))
            {
                int dist = abs(targetR - nr) + abs(targetC - nc);

                if (dist < bestDist)
                {
                    bestDist = dist;
                    bestR = nr;
                    bestC = nc;
                }
            }
        }

        setPosition(bestR, bestC);
    }
};