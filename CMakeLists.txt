cmake_minimum_required(VERSION 3.10)
project(SpaceDestroyer)

set(CMAKE_CXX_STANDARD 17)

# Homebrew install path on Apple Silicon
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(SpaceDestroyer
        src/main.cpp
        src/player.h
        src/player.cpp
        src/game.h
        src/game.cpp
        src/bullet.cpp
        src/bullet.h
        src/block.cpp
        src/block.h
        src/obstacle.cpp
        src/obstacle.h
        src/alien.cpp
        src/alien.h
        src/mysteryShip.cpp
        src/mysteryShip.h
)

# Link raylib and its dependencies
target_link_libraries(SpaceDestroyer raylib m pthread dl)
