main.cpp 
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <ctime>
#include "Player.h"
#include "Ghost.h"

using namespace std;
// states of game
enum GameState
{
    MENU,
    PLAYING,
    GAME_OVER,
    WIN
};
//AI generated pac-man map; Prompt: Generate a pac man map that functions on smfl.
vector<string> map = {
    "############################",
    "#P............#............#",
    "#.####.#####..#..#####.####",
    "#..........................#",
    "#.####.#.##########.#.####.#",
    "#......#.....##.....#......#",
    "######.##### ## #####.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "############################"
};
vector<string> originalMap = map;
//wall recognition
bool isWall(int r, int c)
{
    return r < 0 || r >= map.size() ||
        c < 0 || c >= map[r].size() ||
        map[r][c] == '#';
}
//wall collision physics
bool checkCollision(Player& player, vector<unique_ptr<Ghost>>& ghosts)
{
    for (auto& ghost : ghosts)
    {
        if (player.getRow() == ghost->getRow() &&
            player.getCol() == ghost->getCol())
        {
            return true;
        }
    }
    return false;
}
// sfml map drawing function
void drawMap(sf::RenderWindow& window)
{
    for (int r = 0; r < map.size(); r++)
    {
        for (int c = 0; c < map[r].size(); c++)
        {
            if (map[r][c] == '#')
            {
                sf::RectangleShape wall(sf::Vector2f(TILE - 4, TILE - 4));
                wall.setPosition(sf::Vector2f(c * TILE + 2, r * TILE + 2));
                wall.setFillColor(sf::Color::Black);
                wall.setOutlineThickness(2);
                wall.setOutlineColor(sf::Color(0, 40, 255));
                window.draw(wall);
            }
            else if (map[r][c] == '.')
            {
                sf::CircleShape pellet(3);
                pellet.setPosition(sf::Vector2f(c * TILE + 14, r * TILE + 14));
                pellet.setFillColor(sf::Color(255, 190, 160));
                window.draw(pellet);
            }
        }
    }
}
//main menu sfml function
void drawMenu(sf::RenderWindow& window)
{
    sf::Font font("PressStart2P-Regular.ttf");

    sf::Text title(font);
    title.setString("PAC-MAN");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({ 330, 90 });

    sf::Text start(font);
    start.setString("Press ENTER to Start");
    start.setCharacterSize(28);
    start.setFillColor(sf::Color::White);
    start.setPosition({ 295, 170 });

    sf::Text quit(font);
    quit.setString("Press ESC to Quit");
    quit.setCharacterSize(24);
    quit.setFillColor(sf::Color::White);
    quit.setPosition({ 330, 220 });

    window.draw(title);
    window.draw(start);
    window.draw(quit);
}
// sfml game over screen
void drawGameOver(sf::RenderWindow& window)
{
    sf::Font font("PressStart2P-Regular.ttf");

    sf::Text text(font);
    text.setString("GAME OVER");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition({ 310, 120 });

    sf::Text restart(font);
    restart.setString("Press ENTER to Restart");
    restart.setCharacterSize(26);
    restart.setFillColor(sf::Color::White);
    restart.setPosition({ 295, 190 });

    window.draw(text);
    window.draw(restart);
}
//this tests how many pellets are left and triggers win screen when it hits 0
bool pelletsLeft()
{
    for (int r = 0; r < map.size(); r++)
    {
        for (int c = 0; c < map[r].size(); c++)
        {
            if (map[r][c] == '.')
                return true;
        }
    }

    return false;
}
//sfml win screen
void drawWinScreen(sf::RenderWindow& window)
{
    sf::Font font("PressStart2P-Regular.ttf");

    sf::Text text(font);
    text.setString("YOU WIN!");
    text.setCharacterSize(42);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition({ 310, 120 });

    sf::Text restart(font);
    restart.setString("Press ENTER to Play Again");
    restart.setCharacterSize(20);
    restart.setFillColor(sf::Color::White);
    restart.setPosition({ 260, 190 });

    window.draw(text);
    window.draw(restart);
}
//resets the game back to start
void resetGame(Player& player, vector<unique_ptr<Ghost>>& ghosts)
{
    map = originalMap;

    player.setPosition(1, 1);

    ghosts.clear();
    ghosts.push_back(make_unique<ChaserGhost>(3, 26));
    ghosts.push_back(make_unique<RandomGhost>(9, 5));
    ghosts.push_back(make_unique<AmbushGhost>(9, 22));
}
//MAIN YEA
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode({ 896, 352 }), "Pac-Man");
    window.setFramerateLimit(60);

    GameState state = MENU;

    Player player(1, 1);

    vector<unique_ptr<Ghost>> ghosts;
    ghosts.push_back(make_unique<ChaserGhost>(3, 26));
    ghosts.push_back(make_unique<RandomGhost>(9, 5));
    ghosts.push_back(make_unique<AmbushGhost>(9, 22));

    sf::Clock playerClock;
    sf::Clock ghostClock;

    float playerDelay = 0.18f;
    float ghostDelay = 0.35f;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
// key/control mapping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        if (state == MENU)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                resetGame(player, ghosts);
                state = PLAYING;
            }
        }
        else if (state == GAME_OVER)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                resetGame(player, ghosts);
                state = PLAYING;
            }
        }
        else if (state == PLAYING)
        {
            if (playerClock.getElapsedTime().asSeconds() >= playerDelay)
            {
                int newR = player.getRow();
                int newC = player.getCol();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) newR--;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) newR++;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) newC--;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) newC++;

                if (!isWall(newR, newC))
                    player.setPosition(newR, newC);

                if (map[player.getRow()][player.getCol()] == '.')
                {
                    map[player.getRow()][player.getCol()] = ' ';

                    if (!pelletsLeft())
                        state = WIN;
                }

                playerClock.restart();
            }

            if (ghostClock.getElapsedTime().asSeconds() >= ghostDelay)
            {
                for (auto& ghost : ghosts)
                    ghost->move(map, player.getRow(), player.getCol());

                ghostClock.restart();
            }

            if (checkCollision(player, ghosts))
                state = GAME_OVER;
        }
        else if (state == WIN)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                resetGame(player, ghosts);
                state = PLAYING;
            }
        }

        window.clear(sf::Color::Black);

        if (state == MENU)
            drawMenu(window);
        else if (state == PLAYING)
        {
            drawMap(window);
            player.draw(window);

            for (auto& ghost : ghosts)
                ghost->draw(window);
        }
        else if (state == GAME_OVER)
            drawGameOver(window);
        else if (state == WIN)
        {
            drawWinScreen(window);
        }

        window.display();
    }

    return 0;
}
