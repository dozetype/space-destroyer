#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <raylib.h>
#include <vector>
#include "block.h"

class Obstacle {
public:
    static std::vector<std::vector<int>> grid;
    Vector2 position;
    Obstacle(Vector2 position);
    void draw() const;
    std::vector<Block> blocks;

};



#endif //OBSTACLE_H
