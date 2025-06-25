#include <iostream>
#include <raylib.h>
#include "game.h"


std::string FormatWithLeadingZeros(const int number, const int width) {
    const std::string numberText = std::to_string(number);
    const int leadingZeros = width - numberText.length();
    return std::string(leadingZeros, '0') + numberText;
}

int main(){
    constexpr int offset = 50;
    constexpr int windowWidth = 700;
    constexpr int windowHeight = 650;
    constexpr Color grey = {30, 30, 30, 255};
    constexpr Color yellow = {243, 216, 63, 255};

    InitWindow(windowWidth+offset, windowHeight+2*offset, "hello");
    SetTargetFPS(60);
    InitAudioDevice();

    const Texture2D playerImage = LoadTexture("Graphics/spaceship.png");
    const Font font = LoadFontEx("Font/monogram.ttf", 64, nullptr, 0);
    Game game;

    while (WindowShouldClose() == false) {
        // UpdateMusicStream(game.music);
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
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 3, yellow);
        //
        DrawTextEx(font, "HIGH-SCORE", {520, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highScore, 5);
        DrawTextEx(font, highscoreText.c_str(), {605, 40}, 34, 2, yellow);
        //
        std::string title = "FPS: " + std::to_string(GetFPS());
        SetWindowTitle(title.c_str());

        game.update();
        game.draw();
        game.handleInput();

        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    UnloadTexture(playerImage);
}
