#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

enum GameState {
    MENU,
    GAMEPLAY,
    GAME_OVER
};

void initializeAppleGrid(std::vector<std::vector<SDL_Rect>>& applePositions, int SCREEN_WIDTH,
                        int SCREEN_HEIGHT, int GRID_ROWS, int GRID_COLS, int APPLE_SIZE, int MARGIN);

void resetGame(std::vector<std::vector<int>>& numbers, std::vector<std::vector<bool>>& visible,
               int GRID_ROWS, int GRID_COLS);

void handleEvents(SDL_Event& e, GameState& gameState, SDL_Rect& startButtonRect, SDL_Rect& musicButtonRect,
                  SDL_Rect& highScoreButtonRect, SDL_Rect& exitButtonRect, SDL_Rect& yesButtonRect,
                  SDL_Rect& noButtonRect, SDL_Rect& playAgainButtonRect, SDL_Rect& exitGameButtonRect,
                  int& mouseX, int& mouseY, bool& showMusicOptions, bool& musicOn, bool& musicPlaying,
                  Mix_Music* music, Mix_Chunk* pingSound, Mix_Chunk* gameOverSound, bool& isDragging,
                  SDL_Point& dragStart, SDL_Rect& dragRect, std::vector<std::vector<int>>& numbers,
                  std::vector<std::vector<bool>>& visible, std::vector<std::vector<bool>>& currentlyHighlighted,
                  const std::vector<std::vector<SDL_Rect>>& applePositions, int& score, int& highScore,
                  Uint32& startTime, bool& gameOver, bool& hasWon, int GRID_ROWS, int GRID_COLS, int APPLE_SIZE);

void updateGameState(bool& gameOver, bool& hasWon, GameState& gameState,
                     const std::vector<std::vector<bool>>& visible, int GRID_ROWS, int GRID_COLS,
                     Uint32 currentTime, Uint32 startTime, const Uint32 GAME_TIME, bool& musicPlaying,
                     Mix_Music* music, Mix_Chunk* gameOverSound);

void runGame(SDL_Window* window, SDL_Renderer* renderer);

#endif
