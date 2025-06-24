#ifndef ALIEN_H
#define ALIEN_H
#include <raylib.h>


class Alien {
public:
    static Texture2D alienImages[3];
    Vector2 position;
    int type;

    Alien(int type, Vector2 position);
    void update(int direction);
    void draw() const;
    int getType() const;
    static void unloadImages();
    Rectangle getRec();


private:

};



#endif //ALIEN_H
