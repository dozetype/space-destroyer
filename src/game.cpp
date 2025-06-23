#include "game.h"

#include <iostream>

Game::Game() {
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
    alienLastFired = 0.0;
}

Game::~Game() {
    Alien::unloadImages();
}

void Game::update() {
    for (auto& bullet: player.bullets) {
        bullet.update();
    }
    deleteInactiveBullets();
    moveAliens();
    alienShootBullets();
    for (auto& bullet: alienBullets) {
        bullet.update();
    }
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

    for (auto& bullet: alienBullets) {
        bullet.draw();
    }
}

void Game::handleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        player.moveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player.moveRight();
    }
    else if (IsKeyDown(KEY_SPACE)) {
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

    for (auto b=alienBullets.begin(); b!=alienBullets.end();) {
        if (!b->active) {
            b = alienBullets.erase(b);
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
            int alienType;
            if(i == 0) {
                alienType = 3;
            } else if (i == 1 || i == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = xOff + j * 55;
            float y = yOff + i * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::moveAliens() {
    for (auto& alien: aliens) {
        alien.update(alienDirection);
        if (alien.position.x<=0 || alien.position.x+alien.alienImages[alien.type-1].width>=GetScreenWidth()) {
            alienDirection*=-1;
            moveDownAliens(5);
        }
    }
}

void Game::moveDownAliens(const int distance) {
    for (auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::alienShootBullets() {
    const int randomNum = GetRandomValue(0, aliens.size()-1);
    const Alien& alien = aliens[randomNum];
    if (GetTime()-alienLastFired>=aliensBulletShootInterval && !aliens.empty()) {
        alienBullets.push_back(Bullet({alien.position.x + alien.alienImages[alien.type-1].width / 2,
            alien.position.y+alien.alienImages[alien.type-1].height}, -6));
        alienLastFired = GetTime();
    }
}



