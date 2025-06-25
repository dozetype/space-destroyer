#include "bullet.h"

Bullet::Bullet(const Vector2 position, const int speed):
    active(true), position(position), speed(speed) {}

void Bullet::draw() const {
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {200,200,200,255});
    }
}

Rectangle Bullet::getRec() const {
    return {position.x, position.y, 4, 15};
}

void Bullet::update() {
    if (position.y>10 && position.y<GetScreenHeight()-90) {
        position.y -= speed;
    }
    else {
        active = false;
    }
}