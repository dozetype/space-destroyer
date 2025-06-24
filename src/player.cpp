#include "player.h"

#include <iostream>
#include <ostream>

#include "bullet.h"

Player::Player() {
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth()-image.width) / 2;
    position.y = (GetScreenHeight()-image.height) - 20;
    lastFireTime = 0.0;
}

Player::~Player() {
    UnloadTexture(image);
}

void Player::draw() {
    DrawTextureV(image, position, WHITE);
}

void Player::moveLeft() {
    if (position.x>0) {
        position.x-=5;
    }
}

void Player::moveRight() {
    if (position.x < GetScreenWidth()-image.width) {
        position.x+=5;
    }
}

void Player::fireLaser() {
    if (GetTime() - lastFireTime >= 0.3) {
        bullets.push_back(Bullet({position.x+image.width/2 - 2, position.y-image.height/2}, 7));
        lastFireTime = GetTime();
    }
}

Rectangle Player::getRec() const {
    return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}
