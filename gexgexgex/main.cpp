#include <iostream>
#include<SDL.h>
#include<vector>
using namespace std; 
class Player {
public:
	SDL_Rect hitbox;
	SDL_Rect hurtbox;

	int speed; 
	bool fall;
	int dx, dy , dir; 
	int add;
	bool onground; 

	Player(int x, int y, int width, int height ) {
		dir = 1; 
		add = 25; 
		onground = false; 
		hitbox = { x - width / 2 , y - height / 2 , width , height };
		hurtbox = { x - width / 2, y - height / 2 , width , height };
		fall = true; 
		
	}
	
	
	void fll() {
		hitbox.y += 1;
		hurtbox.y += 1; 

	}

	void move(int x , int y ) {
		if (dir == -1) {
			add = -50;
			cout << add << endl;
			hurtbox.x = hitbox.x - 50;

		}
		else {
			add = 50;
			hurtbox.x = hitbox.x +50 ;
			cout << add << endl;
		}
		
		dx = x; 
		dy = y;
		hurtbox.x += dx; 
		hurtbox.y += dy; 
		hitbox.x += dx; 
		hitbox.y += dy; 
	}

	bool checkCollision(const vector<SDL_Rect>& platforms) {
		for (const auto& platform : platforms) {
			if (SDL_HasIntersection(&hitbox, &platform)) {
				return true; 
			}
			
		}
		return false; 
	}

};

class Entity {
public : 
	SDL_Rect hitbox; 
	//int x, y, width, height;
	Entity(int x, int y, int width, int height) {
		hitbox = { x , y , width , height };
	}
};



int main(int argc, char * argv[]) {

	Player p1(100, 100, 50, 50 );
	vector<Entity> platforms = {
				{200 , 400 , 150 , 3},
		{400 , 400 , 150 , 3},
		{300 , 300 , 150 , 3},
		{0 , 500 , 800 , 3},
	};

	SDL_Window* window = SDL_CreateWindow("box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//SDL_Rect box = { 300 , 400 , 50 , 50 };
	bool running = true; 
	SDL_Event event; 
	int speed = 10; 
	int dir = 1 ; 
	while (running) {
		int dx = 0 , dy = 0; 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false; 
			}
			//if (event.type == SDL_KEYDOWN) {
			//	if (event.key.keysym.sym == SDLK_UP) { p1.hitbox.y -= speed; };
			//	if (event.key.keysym.sym == SDLK_DOWN) { p1.hitbox.y += speed; };
			//	if (event.key.keysym.sym == SDLK_LEFT) { p1.hitbox.x -= speed; };
			//	if (event.key.keysym.sym == SDLK_RIGHT) { p1.hitbox.x += speed; };
			//
			//	
			//}
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		dir = (state[SDL_SCANCODE_D] ? 1 : dir);
		dir = (state[SDL_SCANCODE_A] ? -1 : dir);
		//cout << dir << endl;
		dx = (state[SDL_SCANCODE_D] ? 5 : 0) - (state[SDL_SCANCODE_A] ? 5 : 0);
		dy = (state[SDL_SCANCODE_S] ? 5 : 0) - (state[SDL_SCANCODE_W] ? 5 : 0);
		p1.dir = dir; 
		p1.move(dx , dy  );
		p1.fll();


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
		SDL_RenderFillRect(renderer, &p1.hitbox);

		if (state[SDL_SCANCODE_J]) {
			SDL_SetRenderDrawColor(renderer, 0, 100, 100, 100);
			SDL_RenderFillRect(renderer, &p1.hurtbox);
		}

		for (const auto& platform : platforms) {
			SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0);
			SDL_RenderFillRect(renderer, &platform.hitbox);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0; 
}