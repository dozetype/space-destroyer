#ifndef ALIEN_H
#define ALIEN_H
#include <raylib.h>


class Alien {
public:
    Texture2D image;
    Vector2 position;
    int type;

    Alien(int type, Vector2 position);
    void update();
    void draw() const;
    int getType() const;
private:

};



#endif //ALIEN_H
