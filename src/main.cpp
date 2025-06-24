#include <iostream>
#include <raylib.h>
#include "game.h"


int main(){
    constexpr int offset = 50;
    constexpr int windowWidth = 700;
    constexpr int windowHeight = 650;
    constexpr Color grey = {30, 30, 30, 255};
    constexpr Color yellow = {243, 216, 63, 255};
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    InitWindow(windowWidth+offset, windowHeight+2*offset, "hello");
    SetTargetFPS(60);
    Game game;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 730, 730}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 680}, {725, 680}, 3, yellow);
        std::string title = "FPS: " + std::to_string(GetFPS());
        SetWindowTitle(title.c_str());

        game.update();
        game.draw();
        game.handleInput();

        EndDrawing();
    }
    CloseWindow();
}
