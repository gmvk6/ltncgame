#include<SDL.h>
#include "Entity.hpp"
using namespace std; 
Entity::Entity(int x, int y, int width, int height) {
	hitbox = { x , y , width , height };
}