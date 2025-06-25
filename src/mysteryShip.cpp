#include "mysteryShip.h"

MysteryShip::MysteryShip() {
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

void MysteryShip::spawn() {
    position.y = 50;
    int side = GetRandomValue(0,1);
    if (side==0) {
        position.x = 25;
        speed = 3;
    }
    else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

void MysteryShip::update() {
    if (alive) {
        position.x += speed;
        if (position.x>GetScreenWidth()-25 || position.x<-image.width+25) {
            alive = false;
        }
    }
}

void MysteryShip::draw() {
    if (alive) {
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle MysteryShip::getRec() {
    if (alive) {
        return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
    }
    else {
        return {0, 0, 0, 0};
    }
}