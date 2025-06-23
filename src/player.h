#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include <vector>
#include "bullet.h"


class Player {
public:
    std::vector<Bullet> bullets;

    Player();
    ~Player();
    void draw();
    void moveLeft();
    void moveRight();
    void fireLaser();

private:
    Texture2D image;
    Vector2 position;
    double lastFireTime;
};

#endif //PLAYER_H
