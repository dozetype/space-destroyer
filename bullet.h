#ifndef BULLET_H
#define BULLET_H
#include <raylib.h>

class Bullet {
public:
    bool active;
    Bullet(Vector2 position, int speed);
    void Update();
    void Draw() const;

private:
    Vector2 position;
    int speed;
};

#endif //BULLET_H
