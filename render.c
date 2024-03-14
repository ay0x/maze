#include "header.h"

void render(State *state, Player* player)
{

	
	ColorRGBA RGBA_Orange = {.r = 0xFF, .g = 0xA5, .b = 0x00, .a = 0xFF}; /* Orange */
	ColorRGBA RGBA_White = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF}; /* White */
	ColorRGBA RGBA_Grey = {.r = 0x80, .g = 0x80, .b = 0x80, .a = 0xFF}; /* Grey */

	for (int x = 0; x < SCREEN_WIDTH; ++x)
	{
        /* Calculate the ray position and direction */
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1; /* x-coordinate in camera space */

        vector2float rayDir = {
            .x = player->dir.x + player->plane.x * cameraX,
            .y = player->dir.y + player->plane.y * cameraX,
        };

        /* wich box of the map we're in */
        vector2int mapBox = {
            .x = (int)player->pos.x, 
            .y = (int)player->pos.y
        };

        /* Length of ray from current position to next x- or y-side */
        vector2float sideDist = {};

        /* Lenth of ray from one x- or y-side to next x- or y-side */
        vector2float deltaDist = {
            .x = (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
            .y = (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y),
        };

        float perpWallDist;

        /* What direction to step in x- or y-direction (either +1 or -1) */
        vector2int stepDir = {};

        bool hit = false; /* was there a wall hit */
        Side side; /* was a NorthSouth or EastWest wall hit */

        /* calculate stepDir and initial sideDist */
        if (rayDir.x < 0) {
            stepDir.x = -1;
            sideDist.x = (player->pos.x - mapBox.x) * deltaDist.x;
        } else {
            stepDir.x = 1;
            sideDist.x = (mapBox.x + 1.0f - player->pos.x) * deltaDist.x;
        }
        if (rayDir.y < 0) {
            stepDir.y = -1;
            sideDist.y = (player->pos.y - mapBox.y) * deltaDist.y;
        } else {
            stepDir.y = 1;
            sideDist.y = (mapBox.y + 1.0f - player->pos.y) * deltaDist.y;
        }

        /* DDA */
        while (!hit) {
            /* jump to next map square */
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                mapBox.x += stepDir.x;
                side = EastWest;
            } else {
                sideDist.y += deltaDist.y;
                mapBox.y += stepDir.y;
                side = NorthSouth;
            }
            /* check if ray has hit a wall */
            if (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)] > 0) {
                hit = true;
            }
        }

        /* Calculate the distance projceted on camera direction */
        /* (Euclidian distance would give fisheye effect) */
        switch (side) {
            case EastWest:
                perpWallDist = (sideDist.x - deltaDist.x);
                break;
            case NorthSouth:
                perpWallDist = (sideDist.y - deltaDist.y);
                break;
        }

        /* Calculate height of line to draw on screen */
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        /* calculate lowest and highest pixel to fill in current stripe */
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2; 
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT;

        /* choose wall color */
        ColorRGBA color;
        switch (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)]) {
            case 1: color = RGBA_Orange; break;
            case 2: color = RGBA_Grey; break;
            case 3: color = RGBA_White; break;
        }

        /* give x and y sides different brightness */
        if (side == NorthSouth) {
            color.r /= 2; 
            color.g /= 2; 
            color.b /= 2; 
        }

        /*Draw*/
        SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(state->renderer, x, drawStart, x, drawEnd);

	}

}