#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "alien.h"
#include "mysteryShip.h"
#include "obstacle.h"
#include "player.h"


class Game {
public:
    bool run;
    int lives;
    int score;
    int highScore;
    Music music;

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
    float aliensBulletShootInterval;
    float alienLastFired;
    float mysteryShipTimeLastSpawn;
    int mysteryShipSpawnInterval;
    Sound explosionSound;


    std::vector<Obstacle> createObstacles();
    static std::vector<Alien> createAliens();
    void deleteInactiveBullets();
    void moveAliens();
    void moveDownAliens(int distance);
    void alienShootBullets();
    void checkForCollisions();
    void gameOver();
    void reset();
    void initGame();
    void checkForHighScore();
    static void saveHighScoreToFile(int highScore);
    static int loadHighScoreFromFile();
};
#endif //GAME_H
