#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "alien.h"
#include "obstacle.h"
#include "player.h"


class Game {
public:
    Game();
    ~Game();
    void draw();
    void update();
    void handleInput();

private:
    std::vector<Obstacle> createObstacles();
    std::vector<Alien> createAliens();
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    Player player;

    void deleteInactiveBullets();
};
#endif //GAME_H
