#include "game.h"

#include <iostream>

//Constructor
Game::Game() {
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
    alienLastFired = 0.0;
    mysteryShipTimeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

//Destructor
Game::~Game() {
    Alien::unloadImages();
}

void Game::update() {
    /**
     * Spawning Mystery Ship at a random interval
     */
    if (GetTime()-mysteryShipTimeLastSpawn>mysteryShipSpawnInterval) {
        mysteryShip.spawn();
        mysteryShipTimeLastSpawn = GetTime();
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
    }
    for (auto& bullet: player.bullets) {
        bullet.update();
    }
    for (auto& bullet: alienBullets) {
        bullet.update();
    }
    deleteInactiveBullets();
    moveAliens();
    alienShootBullets();
    mysteryShip.update();
    checkForCollisions();
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

    mysteryShip.draw();
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
    const float gap = (GetScreenWidth()-(4*obstacleWidth))/5;
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
    constexpr int gap = 55;
    const float xOff = GetScreenWidth()/2 - 5*gap;
    const float yOff = GetScreenHeight()/2 - 2.5*gap -100;
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

            const float x = xOff + j * gap;
            const float y = yOff + i * gap;
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

void Game::checkForCollisions() {
    for (auto& bullet: player.bullets) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRec(), bullet.getRec())) {
                it = aliens.erase(it);
                bullet.active = false;
            }
            else
                ++it;
        }
    }
}
