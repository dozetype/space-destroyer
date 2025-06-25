#include "player.h"

#include <iostream>
#include <ostream>

#include "bullet.h"

Player::Player() {
    image = LoadTexture("Graphics/spaceship.png");
    bulletSound = LoadSound("Sounds/laser.ogg");
    init();
}

Player::~Player() {
    UnloadTexture(image);
    UnloadSound(bulletSound);
}

void Player::draw() {
    DrawTextureV(image, position, WHITE);
}

void Player::moveLeft() {
    if (position.x>25) {
        position.x-=5;
    }
}

void Player::moveRight() {
    if (position.x < GetScreenWidth()-image.width-25) {
        position.x+=5;
    }
}

void Player::fireLaser() {
    if (GetTime() - lastFireTime >= 0.3) {
        bullets.push_back(Bullet({position.x+image.width/2 - 2, position.y-image.height/2}, 7));
        lastFireTime = GetTime();
        PlaySound(bulletSound);
    }
}

Rectangle Player::getRec() const {
    return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}

void Player::reset() {
    init();
    bullets.clear();
}

void Player::init() {
    position.x = (GetScreenWidth()-image.width) / 2.0f;
    position.y = (GetScreenHeight()-image.height) - 100;
    lastFireTime = 0.0;
}
