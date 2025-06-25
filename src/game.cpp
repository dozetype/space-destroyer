#include "game.h"

#include <fstream>
#include <iostream>

//Constructor
Game::Game() {
    // music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    // PlayMusicStream(music);
    initGame();
}

//Destructor
Game::~Game() {
    // UnloadMusicStream(music);
    UnloadSound(explosionSound);
    Alien::unloadImages();
}

void Game::update() {
    if (run) {
        // Spawning Mystery Ship at a random interval
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
    else {
        if (IsKeyDown(KEY_ENTER)) {
            reset();
        }
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

    mysteryShip.draw();
}

void Game::handleInput() {
    if (run) {
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
        obstacles.push_back(Obstacle({x, static_cast<float>(GetScreenHeight())-220}));
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
    const float yOff = GetScreenHeight()/2 - 2.5*gap -150;
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
        if (alien.position.x<=25 || alien.position.x+alien.alienImages[alien.type-1].width>=GetScreenWidth()-25) {
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
    //PLAYER Bullets
    for (auto& bullet: player.bullets) {
        auto it = aliens.begin();
        //Aliens
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRec(), bullet.getRec())) {
                if (it->type == 1) score += 100;
                else if (it->type == 2) score += 200;
                else if (it->type == 3) score += 300;
                checkForHighScore();
                it = aliens.erase(it);
                bullet.active = false;
                PlaySound(explosionSound);
            }
            else ++it;
        }

        if (!bullet.active) continue;

        //Obstacles block
        for (auto& ob: obstacles) {
            auto itOb = ob.blocks.begin();
            while (itOb != ob.blocks.end()) {
                if (CheckCollisionRecs(itOb->getRec(), bullet.getRec())) {
                    itOb = ob.blocks.erase(itOb);
                    bullet.active = false;
                }
                else ++itOb;
            }
        }

        //Mystery Ship
        if (CheckCollisionRecs(mysteryShip.getRec(), bullet.getRec())) {
            mysteryShip.alive = false;
            bullet.active = false;
            score += 1000;
            checkForHighScore();
            PlaySound(explosionSound);
        }
    }

    //ALIEN Bullets
    for (auto& bullet: alienBullets) {
        //Player
        if (CheckCollisionRecs(player.getRec(), bullet.getRec())) {
            bullet.active = false;
            lives--;
            if (lives==0) {
                gameOver();
            }
        }

        if (!bullet.active) continue;

        //Obstacles Block
        for (auto& ob: obstacles) {
            auto it = ob.blocks.begin();
            while (it != ob.blocks.end()) {
                if (CheckCollisionRecs(it->getRec(), bullet.getRec())) {
                    it = ob.blocks.erase(it);
                    bullet.active = false;
                }
                else ++it;
            }
        }
    }

    //Alien Collision with Obstacles
    for (auto& alien: aliens) {
        for (auto& ob: obstacles) {
            auto it = ob.blocks.begin();
            while (it != ob.blocks.end()) {
                if (CheckCollisionRecs(it->getRec(), alien.getRec())) {
                    it = ob.blocks.erase(it);
                }
                else ++it;
            }
        }
        if (CheckCollisionRecs(alien.getRec(), player.getRec())) {
            gameOver();
        }
    }
}

void Game::gameOver() {
    std::cout << "Game Over!" <<std::endl;
    run = false;
}

void Game::reset() {
    player.reset();
    aliens.clear();
    alienBullets.clear();
    obstacles.clear();
    initGame();
}

void Game::initGame() {
    run = true;
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
    alienLastFired = 0.0;
    mysteryShipTimeLastSpawn = 0.0;
    aliensBulletShootInterval = 0.35;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    highScore = loadHighScoreFromFile();
}

void Game::checkForHighScore() {
    if (score > highScore) {
        highScore = score;
        saveHighScoreToFile(highScore);
    }
}

void Game::saveHighScoreToFile(int highScore) {
    if (std::ofstream highScoreFile("highscore.txt"); highScoreFile.is_open()) {
        highScoreFile << highScore;
        highScoreFile.close();
    }
    else {
        std::cerr << "Failed to SAVE highscore to file!" << std::endl;
    }
}

int Game::loadHighScoreFromFile() {
    int loadedHighScore = 0;
    if (std::ifstream highScoreFile("highscore.txt"); highScoreFile.is_open()) {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    }
    else {
        std::cerr << "Failed to LOAD highscore from file!" << std::endl;
    }
    return loadedHighScore;
}