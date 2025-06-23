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
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Bullet> alienBullets;
    Player player;
    int alienDirection;
    constexpr static float aliensBulletShootInterval=0.35;
    float alienLastFired;

    std::vector<Obstacle> createObstacles();
    std::vector<Alien> createAliens();
    void deleteInactiveBullets();
    void moveAliens();
    void moveDownAliens(int distance);
    void alienShootBullets();

};
#endif //GAME_H
