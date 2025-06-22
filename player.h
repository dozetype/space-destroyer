#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

class Player {
public:
    Player();
    ~Player();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();

private:
    Texture2D image;
    Vector2 position;
};

#endif //PLAYER_H
