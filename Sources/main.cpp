#include "sdl_utils.h"
#include "game_logic.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "Fruit Box";

int main(int argc, char* argv[]) {

    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window, SCREEN_WIDTH, SCREEN_HEIGHT); 

    runGame(window, renderer);

    quitSDL(window, renderer);
    return 0;
}
