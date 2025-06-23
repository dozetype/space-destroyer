cmake_minimum_required(VERSION 3.10)
project(SpaceDestroyer)

set(CMAKE_CXX_STANDARD 17)

# Homebrew install path on Apple Silicon
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(SpaceDestroyer
        main.cpp
        hello.cpp
        Player.h
        Player.cpp
        game.h
        game.cpp
        bullet.cpp
        bullet.h)

# Link raylib and its dependencies
target_link_libraries(SpaceDestroyer raylib m pthread dl)
