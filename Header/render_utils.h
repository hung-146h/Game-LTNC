#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

void renderMenu(SDL_Renderer* renderer, SDL_Texture* backgroundMenu, TTF_Font* font, TTF_Font* titleFont,
                SDL_Rect& startButtonRect, SDL_Rect& musicButtonRect, SDL_Rect& highScoreButtonRect,
                SDL_Rect& exitButtonRect, SDL_Rect& yesButtonRect, SDL_Rect& noButtonRect,
                int mouseX, int mouseY, bool showMusicOptions, bool& musicOn, int highScore,
                int SCREEN_WIDTH, int SCREEN_HEIGHT);

void renderGameOverMenu(SDL_Renderer* renderer, SDL_Texture* background, TTF_Font* font,
                        SDL_Rect& playAgainButtonRect, int mouseX, int mouseY, int score, bool hasWon,
                        int SCREEN_WIDTH, int SCREEN_HEIGHT);

void renderGame(SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* apple, TTF_Font* font,
                const std::vector<std::vector<int>>& numbers, const std::vector<std::vector<bool>>& visible,
                const std::vector<std::vector<SDL_Rect>>& applePositions,
                const std::vector<std::vector<bool>>& currentlyHighlighted,
                bool isDragging, const SDL_Rect& dragRect, int score, Uint32 currentTime,
                Uint32 startTime, const Uint32 GAME_TIME, SDL_Rect& exitGameButtonRect,
                int mouseX, int mouseY, int SCREEN_WIDTH, int SCREEN_HEIGHT);

#endif
