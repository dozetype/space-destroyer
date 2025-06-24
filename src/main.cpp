#include <iostream>
#include <raylib.h>
#include "game.h"


int main(){
    constexpr int windowHeight = 640;
    constexpr int windowWidth = 760;
    constexpr Color grey = {30, 30, 30, 255};

    InitWindow(windowWidth, windowHeight, "hello");
    SetTargetFPS(60);
    Game game;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(grey);

        std::string title = "FPS: " + std::to_string(GetFPS());
        SetWindowTitle(title.c_str());

        game.update();
        game.draw();
        game.handleInput();

        EndDrawing();
    }
    CloseWindow();
}
