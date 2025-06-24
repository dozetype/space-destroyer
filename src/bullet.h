#ifndef BULLET_H
#define BULLET_H
#include <raylib.h>

class Bullet {
public:
    bool active;
    Bullet(Vector2 position, int speed);
    void update();
    void draw() const;
    Rectangle getRec();

private:
    Vector2 position;
    int speed;
};

#endif //BULLET_H
