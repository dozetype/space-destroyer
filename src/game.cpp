#include "game.h"

#include <iostream>

Game::Game() {
    obstacles = createObstacles();
    aliens = createAliens();
}

Game::~Game() {
}

void Game::update() {
    for (auto& bullet: player.bullets) {
        bullet.update();
    }
    deleteInactiveBullets();
}


void Game::draw() {
    player.draw();

    for (auto bullet: player.bullets) {
        bullet.draw();
    }

    for (auto& ob: obstacles) {
        ob.draw();
    }

    for (auto& alien: aliens) {
        alien.draw();
    }
}

void Game::handleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        player.moveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player.moveRight();
    }
    if (IsKeyDown(KEY_SPACE)) {
        player.fireLaser();
    }
}

void Game::deleteInactiveBullets() {
    for (auto b=player.bullets.begin(); b!=player.bullets.end();) {
        if (!b->active) {
            b = player.bullets.erase(b);
        }
        else {
            ++b;
        }
    }
}

std::vector<Obstacle> Game::createObstacles() {
    const int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth()-(4*obstacleWidth))/5;
    printf("%d, %f", obstacleWidth, gap);

    float x{};
    for (int i=0; i<4; i++) {
        x+=gap;
        obstacles.push_back(Obstacle({x, static_cast<float>(GetScreenHeight())-130}));
        x+=obstacleWidth;
    }
    for (auto ob: obstacles) {
        std::cout << ob.position.x << std::endl;
    }
    return obstacles;
}

std::vector<Alien> Game::createAliens() {
    std::vector<Alien> aliens;
    float xOff = GetScreenWidth()/2 - 5*55;
    float yOff = GetScreenHeight()/2 - 2.5*55 -100;
    for (int i{0}; i<5; i++) {
        for (int j{0}; j<10; j++) {
            float x = xOff + j * 55;
            float y = yOff + i * 55;
            aliens.push_back(Alien(1, {x, y}));
        }
    }
    return aliens;
}


