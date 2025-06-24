#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>

class Block {
public:
    Block(Vector2 position);
    void draw() const;
    Rectangle getRec() const;

private:
    Vector2 position;
};



#endif //BLOCK_H
