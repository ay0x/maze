#include "header.h"
/**
 * main - Entry
 * return: 0 if successful
 */

const float playerFOV = (PI / 2.0f);
const float maxDepth = 20.0f;


int main(void)
{
	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
		   "SDL failed to initialize; %s\n",
		   SDL_GetError());
	State state = {
        .quit = false,
    };
	state.window =
		SDL_CreateWindow("The Maze",
						 SDL_WINDOWPOS_CENTERED_DISPLAY(0),
						 SDL_WINDOWPOS_CENTERED_DISPLAY(0),
						 SCREEN_WIDTH,
						 SCREEN_HEIGHT,
						 SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	ASSERT(state.window,
		   "failed to create SDL window: %s\n",
		   SDL_GetError());

	state.renderer =
		SDL_CreateRenderer(state.window,
						   -1,
						   SDL_RENDERER_PRESENTVSYNC);
	ASSERT(state.renderer,
		   "failed to create SDL renderer: %s\n",
		   SDL_GetError());

	Player player = {
        .pos = {.x =  7.0f, .y =  7.0f},
        .dir = {.x = -1.0f, .y =  0.0f},
        .plane = {.x = 0.0f, .y = 0.66f},
    };

	const float rotateSpeed = 0.05, moveSpeed = 0.05;
	
	while (!state.quit)
	{
		SDL_Event event;
        int mouse_xrel = 0;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
		        case SDL_QUIT:
		        	state.quit = true;
		        	break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_q: /*Rotate left*/
                            rotatePlayer(&player, 1);
                            break;
                        case SDLK_e: /*Rotate right*/
                            rotatePlayer(&player, -1);
                            break;
                    break;
                    }
                break;
            }
		}

        const uint8_t* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_ESCAPE]) state.quit = true;

        vector2float deltaPos = {
            .x = player.dir.x * moveSpeed,
            .y = player.dir.y * moveSpeed,
        };
        if (keystate[SDL_SCANCODE_W]) { /*forwards*/
            if (MAP[xy2index(
                        player.pos.x + deltaPos.x, 
                        player.pos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.x += deltaPos.x;
            }
            if (MAP[xy2index(
                        player.pos.x, 
                        player.pos.y + deltaPos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.y += deltaPos.y;
            }
        }
        if (keystate[SDL_SCANCODE_S]) { /*backwards*/
            if (MAP[xy2index(
                        player.pos.x - deltaPos.x, 
                        player.pos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.x -= deltaPos.x;
            }
            if (MAP[xy2index(
                        player.pos.x, 
                        player.pos.y - deltaPos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.y -= deltaPos.y;
            }
        }
        if (keystate[SDL_SCANCODE_A]) { /*move left*/
            if (MAP[xy2index(
                        player.pos.x - deltaPos.y, 
                        player.pos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.x -= deltaPos.y;
            }
            if (MAP[xy2index(
                        player.pos.x, 
                        player.pos.y - -deltaPos.x, 
                        MAP_SIZE)] == 0) {
                player.pos.y -= -deltaPos.x;
            }
        }
        if (keystate[SDL_SCANCODE_D]) { /*move right*/
            if (MAP[xy2index(
                        player.pos.x - -deltaPos.y, 
                        player.pos.y, 
                        MAP_SIZE)] == 0) {
                player.pos.x -= -deltaPos.y;
            }
            if (MAP[xy2index(
                        player.pos.x, 
                        player.pos.y - deltaPos.x, 
                        MAP_SIZE)] == 0) {
                player.pos.y -= deltaPos.x;
            }
        }

        SDL_SetRenderDrawColor(state.renderer, 0x18, 0x18, 0x18, 0xFF);
        SDL_RenderClear(state.renderer);

		render(&state, &player);

		SDL_RenderPresent(state.renderer);
	}

	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	return 0;
}
