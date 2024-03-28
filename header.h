#ifndef MAIN_H_
#define MAIN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

extern const uint8_t MAP[];


#define ASSERT(condition, ...)                                                      \
  if (!condition) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_SIZE 16
#define PI 3.14159265f
#define texWidth 64
#define texHeight 64

typedef enum {NorthSouth, EastWest} Side;

typedef struct
{
    float x, y;
} vector2float;

typedef struct
{
    int x, y;
} vector2int;

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool quit;
} State;

typedef struct
{
	vector2float pos;
	vector2float dir;
    vector2float plane;
} Player;

typedef struct{
    uint8_t r,g,b,a;
} ColorRGBA;

int xy2index(int x, int y, int w);
void render(State *state, Player* player);
void rotatePlayer(Player* player, int direction);
void drawBuffer(Uint32* buffer, State* state);


#endif