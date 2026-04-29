/* Authors: CB, SH, YG, LF
* Course : CPTS 122
* Assignment : Programming Assignment 9
* Project : Pac - Man
 * test.cpp
 *
 * simple tests for pacman project
 * just checking basic stuff works
 */
/*
#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
#include "Ghost.h"

using namespace std;

// small test map
vector<string> testMap = {
    "#####",
    "#...#",
    "#.#.#",
    "#...#",
    "#####"
};

// check if wall
bool isWall(int r, int c)
{
    if (r < 0 || r >= testMap.size()) return true;
    if (c < 0 || c >= testMap[r].size()) return true;
    if (testMap[r][c] == '#') return true;
    return false;
}

// check if player hits ghost
bool checkCollision(Player& player, vector<unique_ptr<Ghost>>& ghosts)
{
    for (auto& g : ghosts)
    {
        if (player.getRow() == g->getRow() &&
            player.getCol() == g->getCol())
        {
            return true;
        }
    }
    return false;
}

int main()
{
    cout << "starting tests...\n";

    // test 1: move player
    Player p(1, 1);
    p.setPosition(1, 2);

    if (p.getCol() == 2)
        cout << "test 1 ok (move works)\n";
    else
        cout << "test 1 fail\n";

    // test 2: wall check
    if (isWall(0, 0))
        cout << "test 2 ok (wall found)\n";
    else
        cout << "test 2 fail\n";

    // test 3: dont go into wall
    if (isWall(0, 0))
        cout << "test 3 ok (blocked wall)\n";
    else
        cout << "test 3 fail\n";

    // test 4: collision
    vector<unique_ptr<Ghost>> ghosts;
    ghosts.push_back(make_unique<ChaserGhost>(1, 2));

    if (checkCollision(p, ghosts))
        cout << "test 4 ok (collision works)\n";
    else
        cout << "test 4 fail\n";

    // test 5: ghost move
    ChaserGhost g(2, 2);
    g.move(testMap, p.getRow(), p.getCol());

    cout << "test 5 ghost moved to: "
        << g.getRow() << "," << g.getCol() << "\n";

    cout << "done.\n";
    return 0;
}*/