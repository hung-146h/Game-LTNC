#include "sdl_utils.h"
#include <iostream>
#include <string>

using namespace std;

void logErrorAndExit(const char* msg, const char* error) {
    SDL_Quit();
    cout << msg << ": " << error << endl;
    exit(1);
}


SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("Error", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                         SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logErrorAndExit("Error", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        logErrorAndExit("Error", IMG_GetError());
    }

    if (TTF_Init() == -1) {
        logErrorAndExit("Error", TTF_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0) {
        logErrorAndExit("Error", Mix_GetError());
    }

    return window;
}


SDL_Renderer* createRenderer(SDL_Window* window, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                               SDL_RENDERER_ACCELERATED |
                                               SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logErrorAndExit("Error", SDL_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL) {
        return nullptr;
    }
    return texture;
}


SDL_Texture* createTextTexture(TTF_Font* font, const char* text, SDL_Color color, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == nullptr) {
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        return nullptr;
    }

    return texture;
}


void renderTexture(SDL_Texture* texture, int x, int y, int width, int height, SDL_Renderer* renderer) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = width;
    dest.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

Mix_Chunk* loadSound(const char* filename) {
    Mix_Chunk* sound = Mix_LoadWAV(filename);
    if (sound == NULL) {
        string mp3File = string(filename) + ".mp3";
        sound = Mix_LoadWAV(mp3File.c_str());
        if (sound == NULL) {
            sound = nullptr;
        } else {
            Mix_VolumeChunk(sound, 128);
        }
    } else {
        Mix_VolumeChunk(sound, 128);
    }
    return sound;
}
