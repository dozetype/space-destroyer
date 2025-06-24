#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "alien.h"
#include "mysteryShip.h"
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
    MysteryShip mysteryShip;
    int alienDirection;
    constexpr static float aliensBulletShootInterval=0.35;
    float alienLastFired;
    float mysteryShipTimeLastSpawn;
    int mysteryShipSpawnInterval;


    std::vector<Obstacle> createObstacles();

    static std::vector<Alien> createAliens();
    void deleteInactiveBullets();
    void moveAliens();
    void moveDownAliens(int distance);
    void alienShootBullets();
    void checkForCollisions();

};
#endif //GAME_H
