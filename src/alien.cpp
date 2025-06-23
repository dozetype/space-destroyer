#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position): position(position), type(type) {
    //if alienImages[i].id == 0, means texture not found, Doing this allows images to only be loaded from file once
    if (alienImages[type-1].id==0) {
        switch (type) {
            case 1:
                alienImages[0] = LoadTexture("Graphics/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("Graphics/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("Graphics/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("Graphics/alien_1.png");
                break;
        }
    }
}

void Alien::draw() const {
    DrawTextureV(alienImages[type-1], position, WHITE);
}

int Alien::getType() const {
    return type;
}

void Alien::unload_images() {
    for (int i{0}; i<3; i++) {
        UnloadTexture(alienImages[i]);
    }
}
