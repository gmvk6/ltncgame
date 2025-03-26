#include"Shoot.hpp";

using namespace std; 
Shoot::Shoot(int x, int y, int w, int h , int dir) {
	hitbox = { x , y , w , h };
	d = dir;
}

void Shoot::move() {
	hitbox.x += 15*d; 
}
