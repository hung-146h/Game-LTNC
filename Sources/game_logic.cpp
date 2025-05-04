#include "game_logic.h"
#include "sdl_utils.h"
#include "render_utils.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

void initializeAppleGrid(vector<vector<SDL_Rect>>& applePositions, int SCREEN_WIDTH,
                        int SCREEN_HEIGHT, int GRID_ROWS, int GRID_COLS, int APPLE_SIZE, int MARGIN) {
    int gridWidth = SCREEN_WIDTH - 2 * MARGIN;
    int gridHeight = SCREEN_HEIGHT - 2 * MARGIN;

    int spacingX = (GRID_COLS > 1) ? (gridWidth / (GRID_COLS - 1)) : gridWidth;
    int spacingY = (GRID_ROWS > 1) ? (gridHeight / (GRID_ROWS - 1)) : gridHeight;

    spacingX = min(spacingX, APPLE_SIZE + 2);
    spacingY = min(spacingY, APPLE_SIZE + 2);

    int startX = MARGIN + (gridWidth - (GRID_COLS - 1) * spacingX) / 2;
    int startY = MARGIN + (gridHeight - (GRID_ROWS - 1) * spacingY) / 2;

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int x = (GRID_COLS > 1) ? (startX + col * spacingX) : (startX + gridWidth / 2);
            int y = (GRID_ROWS > 1) ? (startY + row * spacingY) : (startY + gridHeight / 2);
            applePositions[row][col] = {x - APPLE_SIZE / 2, y - APPLE_SIZE / 2, APPLE_SIZE, APPLE_SIZE};
        }
    }
}

void resetGame(vector<vector<int>>& numbers, vector<vector<bool>>& visible, int GRID_ROWS, int GRID_COLS) {
    srand(time(0));
    bool flHas10 = false;
    int totalSum = 0;

    auto resetGame = [&]() {
        totalSum = 0;
        flHas10 = false;

        int kk = 1;
        for (int row = 0; row < GRID_ROWS; row++) {
            for (int col = 0; col < GRID_COLS; col++) {
                if (row == GRID_ROWS - 1 && col == GRID_COLS - 1) {
                    continue;
                }
                numbers[row][col] = (rand() % 9) + 1;
                totalSum += numbers[row][col];
                visible[row][col] = true;
                kk++;
            }
        }

        int lastNumber = 10 - (totalSum % 10);
        if (lastNumber == 10) {
            flHas10 = true;
        }
        numbers[GRID_ROWS - 1][GRID_COLS - 1] = lastNumber;
        totalSum += lastNumber;

        if (flHas10) {
            return false;
        }
        return true;
    };

    while (!resetGame()) {}
}

void handleEvents(SDL_Event& e, GameState& gameState, SDL_Rect& startButtonRect, SDL_Rect& musicButtonRect,
                  SDL_Rect& highScoreButtonRect, SDL_Rect& exitButtonRect, SDL_Rect& yesButtonRect,
                  SDL_Rect& noButtonRect, SDL_Rect& playAgainButtonRect, SDL_Rect& exitGameButtonRect,
                  int& mouseX, int& mouseY, bool& showMusicOptions, bool& musicOn, bool& musicPlaying,
                  Mix_Music* music, Mix_Chunk* pingSound, Mix_Chunk* gameOverSound, bool& isDragging,
                  SDL_Point& dragStart, SDL_Rect& dragRect, vector<vector<int>>& numbers,
                  vector<vector<bool>>& visible, vector<vector<bool>>& currentlyHighlighted,
                  const vector<vector<SDL_Rect>>& applePositions, int& score, int& highScore,
                  Uint32& startTime, bool& gameOver, bool& hasWon, int GRID_ROWS, int GRID_COLS, int APPLE_SIZE,
                  bool& quit) {
    if (e.type == SDL_QUIT) {
        quit = true;
        return;
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        if (gameState == MENU) {
            quit = true;
        } else {
            gameState = MENU;
            Mix_HaltMusic();
            musicPlaying = false;
            gameOver = false;
            hasWon = false;
            for (int row = 0; row < GRID_ROWS; row++) {
                for (int col = 0; col < GRID_COLS; col++) {
                    visible[row][col] = true;
                    currentlyHighlighted[row][col] = false;
                }
            }
            resetGame(numbers, visible, GRID_ROWS, GRID_COLS);
        }
        return;
    } else if (gameState == MENU && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        mouseX = e.button.x;
        mouseY = e.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (!showMusicOptions) {
            if (SDL_PointInRect(&mousePoint, &startButtonRect)) {
                if (pingSound != nullptr) {
                    Mix_PlayChannel(-1, pingSound, 0);
                }
                gameState = GAMEPLAY;
                startTime = SDL_GetTicks();
                score = 0;
                gameOver = false;
                hasWon = false;
                if (musicOn && !musicPlaying) {
                    if (Mix_PlayMusic(music, -1) == -1) {
                    } else {
                        musicPlaying = true;
                    }
                }
                for (int row = 0; row < GRID_ROWS; row++) {
                    for (int col = 0; col < GRID_COLS; col++) {
                        visible[row][col] = true;
                        currentlyHighlighted[row][col] = false;
                    }
                }
                resetGame(numbers, visible, GRID_ROWS, GRID_COLS);
            } else if (SDL_PointInRect(&mousePoint, &musicButtonRect)) {
                if (pingSound != nullptr) {
                    Mix_PlayChannel(-1, pingSound, 0);
                }
                showMusicOptions = true;
            } else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {
                if (pingSound != nullptr) {
                    Mix_PlayChannel(-1, pingSound, 0);
                }
                quit = true; 
            }
        } else {
            if (SDL_PointInRect(&mousePoint, &yesButtonRect)) {
                if (pingSound != nullptr) {
                    Mix_PlayChannel(-1, pingSound, 0);
                }
                musicOn = true;
                showMusicOptions = false;
            } else if (SDL_PointInRect(&mousePoint, &noButtonRect)) {
                if (pingSound != nullptr) {
                    Mix_PlayChannel(-1, pingSound, 0);
                }
                musicOn = false;
                Mix_HaltMusic();
                musicPlaying = false;
                showMusicOptions = false;
            }
        }
    } else if (gameState == GAMEPLAY && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        mouseX = e.button.x;
        mouseY = e.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (SDL_PointInRect(&mousePoint, &exitGameButtonRect)) {
            if (pingSound != nullptr) {
                Mix_PlayChannel(-1, pingSound, 0);
            }
            gameState = MENU; 
            Mix_HaltMusic();
            musicPlaying = false;
            gameOver = false;
            hasWon = false;
            for (int row = 0; row < GRID_ROWS; row++) {
                for (int col = 0; col < GRID_COLS; col++) {
                    visible[row][col] = true;
                    currentlyHighlighted[row][col] = false;
                }
            }
            resetGame(numbers, visible, GRID_ROWS, GRID_COLS);
        } else if (!gameOver) {
            isDragging = true;
            dragStart.x = mouseX;
            dragStart.y = mouseY;
            dragRect = {dragStart.x, dragStart.y, 0, 0};
        }
    } else if (gameState == GAMEPLAY && e.type == SDL_MOUSEMOTION && isDragging && !gameOver) {
        mouseX = e.motion.x;
        mouseY = e.motion.y;
        int x = mouseX;
        int y = mouseY;
        dragRect.x = min(dragStart.x, x);
        dragRect.y = min(dragStart.y, y);
        dragRect.w = abs(dragStart.x - x);
        dragRect.h = abs(dragStart.y - y);

        for (int row = 0; row < GRID_ROWS; row++) {
            for (int col = 0; col < GRID_COLS; col++) {
                if (!visible[row][col]) {
                    currentlyHighlighted[row][col] = false;
                    continue;
                }
                SDL_Rect appleRect = applePositions[row][col];
                SDL_Rect center = {appleRect.x + APPLE_SIZE / 2, appleRect.y + APPLE_SIZE / 2, 1, 1};
                currentlyHighlighted[row][col] = SDL_HasIntersection(&dragRect, &center); // Sửa lỗi cú pháp: ¢er -> &center
            }
        }
    } else if (gameState == GAMEPLAY && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && isDragging && !gameOver) {
        mouseX = e.button.x;
        mouseY = e.button.y;
        isDragging = false;

        vector<pair<int, int>> selectedApples;
        int sum = 0;
        for (int row = 0; row < GRID_ROWS; row++) {
            for (int col = 0; col < GRID_COLS; col++) {
                if (!visible[row][col]) continue;
                SDL_Rect appleRect = applePositions[row][col];
                SDL_Rect center = {appleRect.x + APPLE_SIZE / 2, appleRect.y + APPLE_SIZE / 2, 1, 1};
                if (SDL_HasIntersection(&dragRect, &center)) { // Sửa lỗi cú pháp: ¢er -> &center
                    selectedApples.push_back({row, col});
                    sum += numbers[row][col];
                }
                currentlyHighlighted[row][col] = false;
            }
        }

        if (sum == 10) {
            if (pingSound != nullptr) {
                Mix_PlayChannel(-1, pingSound, 0);
            }
            score += selectedApples.size();
            for (auto& pos : selectedApples) {
                visible[pos.first][pos.second] = false;
            }
        }
        dragRect = {0, 0, 0, 0};
    } else if (gameState == GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        mouseX = e.button.x;
        mouseY = e.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (SDL_PointInRect(&mousePoint, &playAgainButtonRect)) {
            if (pingSound != nullptr) {
                Mix_PlayChannel(-1, pingSound, 0);
            }
            highScore = max(highScore, score);
            gameState = MENU;
            Mix_HaltMusic();
            musicPlaying = false;
            gameOver = false;
            hasWon = false;
            for (int row = 0; row < GRID_ROWS; row++) {
                for (int col = 0; col < GRID_COLS; col++) {
                    visible[row][col] = true;
                    currentlyHighlighted[row][col] = false;
                }
            }
            resetGame(numbers, visible, GRID_ROWS, GRID_COLS);
        }
    } else if (e.type == SDL_MOUSEMOTION) {
        mouseX = e.motion.x;
        mouseY = e.motion.y;
    }
}

void updateGameState(bool& gameOver, bool& hasWon, GameState& gameState,
                     const vector<vector<bool>>& visible, int GRID_ROWS, int GRID_COLS,
                     Uint32 currentTime, Uint32 startTime, const Uint32 GAME_TIME,
                     bool& musicPlaying, Mix_Music* music, Mix_Chunk* gameOverSound) {
    bool timeUp = (currentTime - startTime >= GAME_TIME);

    bool allApplesRemoved = true;
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            if (visible[row][col]) {
                allApplesRemoved = false;
                break;
            }
        }
        if (!allApplesRemoved) break;
    }

    if (timeUp && !gameOver) {
        gameOver = true;
        gameState = GAME_OVER;
        hasWon = false;
        Mix_HaltMusic();
        musicPlaying = false;
        if (gameOverSound != nullptr) {
            Mix_PlayChannel(-1, gameOverSound, 0);
        }
    } else if (allApplesRemoved && !gameOver) {
        gameOver = true;
        gameState = GAME_OVER;
        hasWon = true;
        Mix_HaltMusic();
        musicPlaying = false;
        if (gameOverSound != nullptr) {
            Mix_PlayChannel(-1, gameOverSound, 0);
        }
    }
}

void runGame(SDL_Window* window, SDL_Renderer* renderer) {
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;

    SDL_Texture* backgroundMenu = loadTexture("background_menu.png", renderer);
    if (backgroundMenu == NULL) {
    }

    SDL_Texture* background = loadTexture("background.png", renderer);
    if (background == NULL) {
        if (backgroundMenu != nullptr) SDL_DestroyTexture(backgroundMenu);
        quitSDL(window, renderer);
        return;
    }

    SDL_Texture* apple = loadTexture("apple.png", renderer);
    if (apple == NULL) {
        SDL_DestroyTexture(background);
        if (backgroundMenu != nullptr) SDL_DestroyTexture(backgroundMenu);
        quitSDL(window, renderer);
        return;
    }

    Mix_Music* music = Mix_LoadMUS("aura.mp3");
    if (music == NULL) {
        SDL_DestroyTexture(apple);
        SDL_DestroyTexture(background);
        if (backgroundMenu != nullptr) SDL_DestroyTexture(backgroundMenu);
        quitSDL(window, renderer);
        return;
    }

    Mix_Chunk* pingSound = loadSound("ping.wav");
    if (pingSound == NULL) {
        pingSound = loadSound("ping.mp3");
        if (pingSound == NULL) {
            pingSound = nullptr;
        }
    }

    Mix_Chunk* gameOverSound = loadSound("gameover.wav");
    if (gameOverSound == NULL) {
        gameOverSound = nullptr;
    }

    bool musicPlaying = false;

    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\times.ttf", 36);
    if (font == nullptr) {
    }

    TTF_Font* titleFont = TTF_OpenFont("C:\\Windows\\Fonts\\times.ttf", 48);
    if (titleFont == nullptr) {
    }

    int GRID_ROWS = 10;
    int GRID_COLS = 17;

    if (GRID_ROWS <= 0 || GRID_COLS <= 0) {
        if (pingSound != nullptr) Mix_FreeChunk(pingSound);
        if (gameOverSound != nullptr) Mix_FreeChunk(gameOverSound);
        Mix_FreeMusic(music);
        if (font != nullptr) TTF_CloseFont(font);
        if (titleFont != nullptr) TTF_CloseFont(titleFont);
        SDL_DestroyTexture(apple);
        SDL_DestroyTexture(background);
        if (backgroundMenu != nullptr) SDL_DestroyTexture(backgroundMenu);
        quitSDL(window, renderer);
        return;
    }

    vector<vector<int>> numbers(GRID_ROWS, vector<int>(GRID_COLS, 0));
    vector<vector<bool>> visible(GRID_ROWS, vector<bool>(GRID_COLS, true));
    vector<vector<SDL_Rect>> applePositions(GRID_ROWS, vector<SDL_Rect>(GRID_COLS));
    vector<vector<bool>> currentlyHighlighted(GRID_ROWS, vector<bool>(GRID_COLS, false));

    initializeAppleGrid(applePositions, SCREEN_WIDTH, SCREEN_HEIGHT, GRID_ROWS, GRID_COLS, 48, 30);
    resetGame(numbers, visible, GRID_ROWS, GRID_COLS);

    bool isDragging = false;
    SDL_Rect dragRect = {0, 0, 0, 0};
    SDL_Point dragStart = {0, 0};
    int score = 0;
    int highScore = 0;
    Uint32 startTime = SDL_GetTicks();
    const Uint32 GAME_TIME = 120000;
    bool gameOver = false;
    bool hasWon = false;
    GameState gameState = MENU;
    SDL_Rect startButtonRect = {0, 0, 0, 0};
    SDL_Rect musicButtonRect = {0, 0, 0, 0};
    SDL_Rect highScoreButtonRect = {0, 0, 0, 0};
    SDL_Rect exitButtonRect = {0, 0, 0, 0};
    SDL_Rect yesButtonRect = {0, 0, 0, 0};
    SDL_Rect noButtonRect = {0, 0, 0, 0};
    SDL_Rect playAgainButtonRect = {0, 0, 0, 0};
    SDL_Rect exitGameButtonRect = {0, 0, 0, 0};
    int mouseX = 0, mouseY = 0;
    bool showMusicOptions = false;
    bool musicOn = true;

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            handleEvents(e, gameState, startButtonRect, musicButtonRect, highScoreButtonRect, exitButtonRect,
                         yesButtonRect, noButtonRect, playAgainButtonRect, exitGameButtonRect, mouseX, mouseY,
                         showMusicOptions, musicOn, musicPlaying, music, pingSound, gameOverSound, isDragging,
                         dragStart, dragRect, numbers, visible, currentlyHighlighted, applePositions, score,
                         highScore, startTime, gameOver, hasWon, GRID_ROWS, GRID_COLS, 48, quit);
            
        }

        if (gameState == MENU) {
            renderMenu(renderer, backgroundMenu, font, titleFont, startButtonRect, musicButtonRect,
                       highScoreButtonRect, exitButtonRect, yesButtonRect, noButtonRect, mouseX, mouseY,
                       showMusicOptions, musicOn, highScore, SCREEN_WIDTH, SCREEN_HEIGHT);
        } else if (gameState == GAMEPLAY) {
            Uint32 currentTime = SDL_GetTicks();
            updateGameState(gameOver, hasWon, gameState, visible, GRID_ROWS, GRID_COLS, currentTime,
                            startTime, GAME_TIME, musicPlaying, music, gameOverSound);
            renderGame(renderer, background, apple, font, numbers, visible, applePositions, currentlyHighlighted,
                       isDragging, dragRect, score, currentTime, startTime, GAME_TIME, exitGameButtonRect,
                       mouseX, mouseY, SCREEN_WIDTH, SCREEN_HEIGHT);
        } else if (gameState == GAME_OVER) {
            renderGameOverMenu(renderer, background, font, playAgainButtonRect, mouseX, mouseY, score, hasWon,
                               SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        SDL_Delay(16);
    }

    if (pingSound != nullptr) Mix_FreeChunk(pingSound);
    if (gameOverSound != nullptr) Mix_FreeChunk(gameOverSound);
    Mix_FreeMusic(music);
    if (font != nullptr) TTF_CloseFont(font);
    if (titleFont != nullptr) TTF_CloseFont(titleFont);
    SDL_DestroyTexture(apple);
    SDL_DestroyTexture(background);
    if (backgroundMenu != nullptr) SDL_DestroyTexture(backgroundMenu);
    quitSDL(window, renderer); 
}
