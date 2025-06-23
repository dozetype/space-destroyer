#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <raylib.h>
#include <vector>
#include "block.h"

class Obstacle {
public:
    Obstacle(Vector2 position);
    void Draw() const;

private:
    Vector2 position;
    std::vector<Block> blocks;
    std::vector<std::vector<int>> grid;
};



#endif //OBSTACLE_H
