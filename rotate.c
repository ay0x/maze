#include "header.h"

/**
 * rotatePlayer - Rotates vector's field of view
 * @player: Pointer to the vector
 * @direction: Rotate field of view on the x-axis
 * Return: Nothing
*/

void rotatePlayer(Player *player, int direction)
{
	const float rotateSpeed = 0.025;

	float rotSpeed = rotateSpeed * direction;
    /* Rotate player's direction and plane vectors */
	vector2float oldDir = player->dir;

	player->dir.x = player->dir.x * cosf(rotSpeed)
		- player->dir.y * sinf(rotSpeed);
	player->dir.y = oldDir.x * sinf(rotSpeed)
		+ player->dir.y * cosf(rotSpeed);

	vector2float oldPlane = player->plane;

	player->plane.x = player->plane.x * cosf(rotSpeed)
		- player->plane.y * sinf(rotSpeed);
	player->plane.y = oldPlane.x * sinf(rotSpeed)
		+ player->plane.y * cosf(rotSpeed);
}
