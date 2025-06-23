#include <iostream>
#include <raylib.h>
#include "game.h"


int main(){
    constexpr int windowHeight = 640;
    constexpr int windowWidth = 760;

    InitWindow(windowWidth, windowHeight, "hello");
    SetTargetFPS(60);
    Game game;
    while (WindowShouldClose() == false) {
        constexpr Color grey = {30, 30, 30, 255};
        BeginDrawing();
        ClearBackground(grey);
        game.HandleInput();
        game.Draw();
        game.Update();

        EndDrawing();
    }
    CloseWindow();
}