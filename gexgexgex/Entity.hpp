#pragma once 
#include<SDL.h>
#include<vector>
using namespace std;
class Entity {
public:
	SDL_Rect hitbox;
	Entity(int x, int y, int width, int height);
};