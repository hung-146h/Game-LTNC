#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window, int SCREEN_WIDTH, int SCREEN_HEIGHT); // Thêm tham số
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);
SDL_Texture* createTextTexture(TTF_Font* font, const char* text, SDL_Color color, SDL_Renderer* renderer);
void renderTexture(SDL_Texture* texture, int x, int y, int width, int height, SDL_Renderer* renderer);
Mix_Chunk* loadSound(const char* filename);
#endif
