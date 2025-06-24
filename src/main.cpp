#include <iostream>
#include <raylib.h>
#include "game.h"


std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main(){
    constexpr int offset = 50;
    constexpr int windowWidth = 700;
    constexpr int windowHeight = 650;
    constexpr Color grey = {30, 30, 30, 255};
    constexpr Color yellow = {243, 216, 63, 255};
    InitWindow(windowWidth+offset, windowHeight+2*offset, "hello");
    SetTargetFPS(60);

    const Texture2D playerImage = LoadTexture("Graphics/spaceship.png");
    const Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 730, 730}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 680}, {725, 680}, 3, yellow);
        if(game.run){
            DrawTextEx(font, "LEVEL 01", {510, 695}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {510, 695}, 34, 2, yellow);
        }
        float x = 50.0;
        for(int i = 0; i < game.lives; i ++) {
            DrawTextureV(playerImage, {x, 695}, WHITE);
            x += 50;
        }
        // DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        // std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        // DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);
        //
        // DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        // std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        // DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);
        //
        // std::string title = "FPS: " + std::to_string(GetFPS());
        // SetWindowTitle(title.c_str());

        game.update();
        game.draw();
        game.handleInput();

        EndDrawing();
    }
    CloseWindow();
    // UnloadTexture(playerImage);
}
