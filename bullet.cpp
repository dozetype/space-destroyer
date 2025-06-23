#include "bullet.h"

Bullet::Bullet(const Vector2 position, const int speed):
    active(true), position(position), speed(speed) {}

void Bullet::Draw() const {
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {200,200,200,255});
    }
}

void Bullet::Update() {
    if (position.y>0 && position.y<GetScreenHeight()) {
        position.y -= speed;
    }
    else {
        active = false;
    }

}

