#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H
#include <raylib.h>


class MysteryShip {
public:
    bool alive;

    MysteryShip();
    ~MysteryShip();
    void update();
    void draw();
    void spawn();
    Rectangle getRec();

private:
    Vector2 position;
    Texture2D image;
    int speed;
};



#endif //MYSTERYSHIP_H
