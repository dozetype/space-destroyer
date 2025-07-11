#include "block.h"

Block::Block(const Vector2 position): position(position){}

void Block::draw() const {
    DrawRectangle(position.x, position.y, 3, 3, {200, 40, 100, 255});
}

Rectangle Block::getRec() const {
    return {position.x, position.y, 3,  3};
}

