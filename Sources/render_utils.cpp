#include "render_utils.h"
#include "sdl_utils.h"
#include <sstream>

using namespace std;


void renderMenu(SDL_Renderer* renderer, SDL_Texture* backgroundMenu, TTF_Font* font, TTF_Font* titleFont,
                SDL_Rect& startButtonRect, SDL_Rect& musicButtonRect, SDL_Rect& highScoreButtonRect,
                SDL_Rect& exitButtonRect, SDL_Rect& yesButtonRect, SDL_Rect& noButtonRect,
                int mouseX, int mouseY, bool showMusicOptions, bool& musicOn, int highScore,
                int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    SDL_RenderClear(renderer);

    if (backgroundMenu == nullptr) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);
    } else {
        SDL_RenderCopy(renderer, backgroundMenu, NULL, NULL);
    }

    SDL_Color blackColor = {0, 0, 0, 255};
    SDL_Color yellowColor = {255, 215, 0, 255};
    SDL_Color redColor = {255, 0, 0, 255};     // Màu đỏ cho "Fruit"
    SDL_Color greenColor = {0, 255, 0, 255};   // Màu xanh lá cây đậm hơn cho "Box"


    SDL_Texture* fruitText = createTextTexture(titleFont, "Fruit", redColor, renderer);
    SDL_Texture* boxText = createTextTexture(titleFont, "Box", greenColor, renderer);
    if (fruitText != nullptr && boxText != nullptr) {
        int fruitW, fruitH, boxW, boxH;
        SDL_QueryTexture(fruitText, NULL, NULL, &fruitW, &fruitH);
        SDL_QueryTexture(boxText, NULL, NULL, &boxW, &boxH);
        renderTexture(fruitText, 20, 20, fruitW, fruitH, renderer);
        renderTexture(boxText, 20 + fruitW + 5, 20, boxW, boxH, renderer);
        SDL_DestroyTexture(fruitText);
        SDL_DestroyTexture(boxText);
    }

    if (!showMusicOptions) {

        string startTextStr = "Start Game";
        SDL_Texture* startText = createTextTexture(font, startTextStr.c_str(),
            (mouseX >= startButtonRect.x && mouseX <= startButtonRect.x + startButtonRect.w &&
             mouseY >= startButtonRect.y && mouseY <= startButtonRect.y + startButtonRect.h) ? yellowColor : blackColor, renderer);
        if (startText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(startText, NULL, NULL, &textW, &textH);
            startButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            startButtonRect.y = SCREEN_HEIGHT / 2 - 120;
            startButtonRect.w = textW;
            startButtonRect.h = textH;
            renderTexture(startText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2 - 120, textW, textH, renderer);
            SDL_DestroyTexture(startText);
        }

        string musicTextStr = "Music";
        SDL_Texture* musicText = createTextTexture(font, musicTextStr.c_str(),
            (mouseX >= musicButtonRect.x && mouseX <= musicButtonRect.x + musicButtonRect.w &&
             mouseY >= musicButtonRect.y && mouseY <= musicButtonRect.y + musicButtonRect.h) ? yellowColor : blackColor, renderer);
        if (musicText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(musicText, NULL, NULL, &textW, &textH);
            musicButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            musicButtonRect.y = SCREEN_HEIGHT / 2 - 60;
            musicButtonRect.w = textW;
            musicButtonRect.h = textH;
            renderTexture(musicText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2 - 60, textW, textH, renderer);
            SDL_DestroyTexture(musicText);
        }


        string highScoreTextStr = "High Score: " + to_string(highScore);
        SDL_Texture* highScoreText = createTextTexture(font, highScoreTextStr.c_str(),
            (mouseX >= highScoreButtonRect.x && mouseX <= highScoreButtonRect.x + highScoreButtonRect.w &&
             mouseY >= highScoreButtonRect.y && mouseY <= highScoreButtonRect.y + highScoreButtonRect.h) ? yellowColor : blackColor, renderer);
        if (highScoreText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(highScoreText, NULL, NULL, &textW, &textH);
            highScoreButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            highScoreButtonRect.y = SCREEN_HEIGHT / 2;
            highScoreButtonRect.w = textW;
            highScoreButtonRect.h = textH;
            renderTexture(highScoreText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2, textW, textH, renderer);
            SDL_DestroyTexture(highScoreText);
        }

        string exitTextStr = "Exit Game";
        SDL_Texture* exitText = createTextTexture(font, exitTextStr.c_str(),
            (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
             mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h) ? yellowColor : blackColor, renderer);
        if (exitText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(exitText, NULL, NULL, &textW, &textH);
            exitButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            exitButtonRect.y = SCREEN_HEIGHT / 2 + 60;
            exitButtonRect.w = textW;
            exitButtonRect.h = textH;
            renderTexture(exitText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2 + 60, textW, textH, renderer);
            SDL_DestroyTexture(exitText);
        }
    } else {

        string yesTextStr = "Yes";
        SDL_Texture* yesText = createTextTexture(font, yesTextStr.c_str(),
            (mouseX >= yesButtonRect.x && mouseX <= yesButtonRect.x + yesButtonRect.w &&
             mouseY >= yesButtonRect.y && mouseY <= yesButtonRect.y + yesButtonRect.h) ? yellowColor : blackColor, renderer);
        if (yesText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(yesText, NULL, NULL, &textW, &textH);
            yesButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            yesButtonRect.y = SCREEN_HEIGHT / 2 - 40;
            yesButtonRect.w = textW;
            yesButtonRect.h = textH;
            renderTexture(yesText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2 - 40, textW, textH, renderer);
            SDL_DestroyTexture(yesText);
        }

        string noTextStr = "No";
        SDL_Texture* noText = createTextTexture(font, noTextStr.c_str(),
            (mouseX >= noButtonRect.x && mouseX <= noButtonRect.x + noButtonRect.w &&
             mouseY >= noButtonRect.y && mouseY <= noButtonRect.y + noButtonRect.h) ? yellowColor : blackColor, renderer);
        if (noText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(noText, NULL, NULL, &textW, &textH);
            noButtonRect.x = (SCREEN_WIDTH - textW) / 2;
            noButtonRect.y = SCREEN_HEIGHT / 2 + 40;
            noButtonRect.w = textW;
            noButtonRect.h = textH;
            renderTexture(noText, (SCREEN_WIDTH - textW) / 2, SCREEN_HEIGHT / 2 + 40, textW, textH, renderer);
            SDL_DestroyTexture(noText);
        }
    }

    SDL_RenderPresent(renderer);
}


void renderGameOverMenu(SDL_Renderer* renderer, SDL_Texture* background, TTF_Font* font,
                        SDL_Rect& playAgainButtonRect, int mouseX, int mouseY, int score, bool hasWon,
                        int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    SDL_Color blackColor = {0, 0, 0, 255};
    SDL_Color yellowColor = {255, 215, 0, 255};


    string endGameText = hasWon ? "You Win! Final Score: " + to_string(score) : "Game Over! Final Score: " + to_string(score);
    SDL_Texture* endGameTexture = createTextTexture(font, endGameText.c_str(), blackColor, renderer);
    if (endGameTexture != nullptr) {
        int textW, textH;
        SDL_QueryTexture(endGameTexture, NULL, NULL, &textW, &textH);
        renderTexture(endGameTexture, (SCREEN_WIDTH - textW) / 2, (SCREEN_HEIGHT - textH) / 2 - 50, textW, textH, renderer);
        SDL_DestroyTexture(endGameTexture);
    }

    string playAgainTextStr = "Play Again";
    SDL_Texture* playAgainText = createTextTexture(font, playAgainTextStr.c_str(),
        (mouseX >= playAgainButtonRect.x && mouseX <= playAgainButtonRect.x + playAgainButtonRect.w &&
         mouseY >= playAgainButtonRect.y && mouseY <= playAgainButtonRect.y + playAgainButtonRect.h) ? yellowColor : blackColor, renderer);
    if (playAgainText != nullptr) {
        int textW, textH;
        SDL_QueryTexture(playAgainText, NULL, NULL, &textW, &textH);
        playAgainButtonRect.x = (SCREEN_WIDTH - textW) / 2;
        playAgainButtonRect.y = (SCREEN_HEIGHT - textH) / 2 + 50;
        playAgainButtonRect.w = textW;
        playAgainButtonRect.h = textH;
        renderTexture(playAgainText, (SCREEN_WIDTH - textW) / 2, (SCREEN_HEIGHT - textH) / 2 + 50, textW, textH, renderer);
        SDL_DestroyTexture(playAgainText);
    }

    SDL_RenderPresent(renderer);
}


void renderGame(SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* apple, TTF_Font* font,
                const vector<vector<int>>& numbers, const vector<vector<bool>>& visible,
                const vector<vector<SDL_Rect>>& applePositions, const vector<vector<bool>>& currentlyHighlighted,
                bool isDragging, const SDL_Rect& dragRect, int score, Uint32 currentTime, Uint32 startTime,
                const Uint32 GAME_TIME, SDL_Rect& exitGameButtonRect, int mouseX, int mouseY,
                int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    const int APPLE_SIZE = 48;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    for (int row = 0; row < numbers.size(); row++) {
        for (int col = 0; col < numbers[0].size(); col++) {
            if (!visible[row][col]) continue;

            int x = applePositions[row][col].x + APPLE_SIZE / 2;
            int y = applePositions[row][col].y + APPLE_SIZE / 2;

            if (currentlyHighlighted[row][col]) {
                SDL_SetTextureColorMod(apple, 255, 255, 153);
            } else {
                SDL_SetTextureColorMod(apple, 255, 255, 255);
            }
            renderTexture(apple, x - APPLE_SIZE / 2, y - APPLE_SIZE / 2, APPLE_SIZE, APPLE_SIZE, renderer);

            if (font != nullptr) {
                char numberText[3];
                snprintf(numberText, 3, "%d", numbers[row][col]);
                SDL_Color textColor = currentlyHighlighted[row][col] ? SDL_Color{255, 255, 153, 255} : SDL_Color{255, 255, 255, 255};
                SDL_Texture* numberTexture = createTextTexture(font, numberText, textColor, renderer);
                if (numberTexture == nullptr) {
                    continue;
                }

                int textW, textH;
                SDL_QueryTexture(numberTexture, NULL, NULL, &textW, &textH);
                int textX = x - textW / 2;
                int textY = y - textH / 2 + 5;

                renderTexture(numberTexture, textX, textY, textW, textH, renderer);
                SDL_DestroyTexture(numberTexture);
            }
        }
    }

    if (isDragging) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dragRect);
    }

    if (font != nullptr) {
        string scoreText = "Score: " + to_string(score);
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Texture* scoreTexture = createTextTexture(font, scoreText.c_str(), textColor, renderer);
        if (scoreTexture != nullptr) {
            int textW, textH;
            SDL_QueryTexture(scoreTexture, NULL, NULL, &textW, &textH);
            renderTexture(scoreTexture, 10, 10, textW, textH, renderer);
            SDL_DestroyTexture(scoreTexture);
        }

        int remainingTime = max(0, (int)(GAME_TIME - (currentTime - startTime)) / 1000);
        string timeText = "Time: " + to_string(remainingTime) + "s";
        SDL_Texture* timeTexture = createTextTexture(font, timeText.c_str(), textColor, renderer);
        if (timeTexture != nullptr) {
            int textW, textH;
            SDL_QueryTexture(timeTexture, NULL, NULL, &textW, &textH);
            renderTexture(timeTexture, SCREEN_WIDTH - textW - 10, 10, textW, textH, renderer);
            SDL_DestroyTexture(timeTexture);
        }


        string exitTextStr = "Exit Game";
        SDL_Color blackColor = {0, 0, 0, 255};
        SDL_Color yellowColor = {255, 215, 0, 255};
        SDL_Color exitColor = (mouseX >= exitGameButtonRect.x && mouseX <= exitGameButtonRect.x + exitGameButtonRect.w &&
                              mouseY >= exitGameButtonRect.y && mouseY <= exitGameButtonRect.y + exitGameButtonRect.h) ? yellowColor : blackColor;
        SDL_Texture* exitText = createTextTexture(font, exitTextStr.c_str(), exitColor, renderer);
        if (exitText != nullptr) {
            int textW, textH;
            SDL_QueryTexture(exitText, NULL, NULL, &textW, &textH);
            exitGameButtonRect.x = 10;
            exitGameButtonRect.y = SCREEN_HEIGHT - textH - 10;
            exitGameButtonRect.w = textW;
            exitGameButtonRect.h = textH;
            renderTexture(exitText, 10, SCREEN_HEIGHT - textH - 10, textW, textH, renderer);
            SDL_DestroyTexture(exitText);
        }
    }

    SDL_RenderPresent(renderer);
}
