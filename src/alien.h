#ifndef ALIEN_H
#define ALIEN_H
#include <raylib.h>


class Alien {
public:
    static Texture2D alienImages[3];
    Vector2 position;
    int type;

    Alien(int type, Vector2 position);
    void update();
    void draw() const;
    int getType() const;
    static void unload_images();

private:

};



#endif //ALIEN_H
