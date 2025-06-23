#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H
#include <raylib.h>


class MysteryShip {
public:
    MysteryShip();
    ~MysteryShip();
    void update();
    void draw();
    void spawn();
    bool alive;

private:
    Vector2 position;
    Texture2D image;
    int speed;
};



#endif //MYSTERYSHIP_H
