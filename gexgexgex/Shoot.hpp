#pragma once 
#include <SDL.h>
class Shoot
{
public:
	SDL_Rect hitbox;
	int d;
	Shoot(int x, int y, int w, int h , int dir);
	void move();
};