#include "header.h"

/**
 * xy2index - Find index number using x and y coordinate
 * @x: x-coordinate
 * @y: y-coordinate
 * @w: Width
 * Return: Index number of the 1D array representing 2-D array
*/

int xy2index(int x, int y, int w)
{
	return (y * w + x);
}
