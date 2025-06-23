#include "game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::Update() {
    for (auto& bullet: player.bullets) {
        bullet.Update();
    }
    DeleteInactiveBullets();
}


void Game::Draw() {
    player.Draw();

    for (auto bullet: player.bullets) {
        bullet.Draw();
    }
}

void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        player.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player.MoveRight();
    }
    if (IsKeyDown(KEY_SPACE)) {
        player.FireLaser();
    }
}

void Game::DeleteInactiveBullets() {
    for (auto b=player.bullets.begin(); b!=player.bullets.end();) {
        if (!b->active) {
            b = player.bullets.erase(b);
        }
        else {
            ++b;
        }
    }
}


