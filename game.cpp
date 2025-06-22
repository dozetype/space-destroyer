#include "game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::Draw() {
    player.Draw();
}

void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        player.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player.MoveRight();
    }
}

