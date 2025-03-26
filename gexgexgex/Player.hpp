#pragma once 
#include<SDL.h>
#include<vector>
#include "Entity.hpp"
using namespace std; 
class Player
{
public:
	SDL_Rect hitbox;
	SDL_Rect hurtbox;
	SDL_Rect ground; 
	Player(int x, int y, int width, int height);
	int velocityY;
	bool isOnGround;
	bool canFallThrough;
	int dx, dy, dir;
	int add;

	void move(int x, int y , const vector<Entity>& platforms);
	bool checkCollision(const vector<SDL_Rect>& platforms);
	void applyGravity(const vector<Entity>& platforms);
	void jumb();
	//void fire();
	void fall();

};