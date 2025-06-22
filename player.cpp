#include "player.h"

Player::Player() {
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth()-image.width) / 2;
    position.y = (GetScreenHeight()-image.height) - 50;
}

Player::~Player() {
    UnloadTexture(image);
}

void Player::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Player::MoveLeft() {
    position.x-=5;
}

void Player::MoveRight() {
    position.x+=5;
}




