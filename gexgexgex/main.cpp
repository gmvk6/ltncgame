#include <iostream>
#include<SDL.h>
#include<vector>
#include "Player.hpp"
#include "Entity.hpp"
#include "Shoot.hpp"
using namespace std;

int main(int argc, char * argv[]) {

	Player p1(100, 0, 50, 50 );
	vector<Entity> platforms = {
		{200 ,200 , 150 ,3},
		{600 , 350 , 150 , 3},
		{150 , 400 , 150 , 3},
		{30,300,150,3},
		{400 , 400 , 150 , 3},
		{350 , 300 , 150 , 3},
		{50 , 500 , 700 , 3},
	};
	vector<Shoot> guns; 

	SDL_Window* window = SDL_CreateWindow("brawlhalla", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//SDL_Rect box = { 300 , 400 , 50 , 50 };
	bool running = true; 
	SDL_Event event; 
	int speed = 10; 
	int dir = 1 ; 
	while (running) {
		
		int dx = 0 , dy = 0; 
		if (p1.hitbox.y > 700) {
			p1.hitbox.y = 0; 
			p1.hitbox.x = 350; 

			
		}
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false; 
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_w) p1.jumb();
				if (event.key.keysym.sym == SDLK_s) p1.fall();
			}
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		dir = (state[SDL_SCANCODE_D] ? 1 : dir);
		dir = (state[SDL_SCANCODE_A] ? -1 : dir);
		//cout << dir << endl;
		dx = (state[SDL_SCANCODE_D] ? 5 : 0) - (state[SDL_SCANCODE_A] ? 5 : 0);
		//dy = (state[SDL_SCANCODE_S] ? 5 : 0) - (state[SDL_SCANCODE_W] ? 5 : 0);

		p1.dir = dir; 
		p1.move(dx , dy  , platforms);
		//p1.applyGravity(platforms);
		p1.applyGravity(platforms);
		


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 100, 10*dir, 10*dir);
		SDL_RenderFillRect(renderer, &p1.hitbox);

		if (state[SDL_SCANCODE_J]) {
			SDL_SetRenderDrawColor(renderer, 0, 100*dir, 0, 0);
			SDL_RenderFillRect(renderer, &p1.hurtbox);
		}
		if (state[SDL_SCANCODE_K]) {
			guns.push_back({ p1.hitbox.x + 25,p1.hitbox.y , 5, 5  , dir});
		}

		// Duyệt qua vector từ đầu đến cuối, xóa phần tử đúng cách



		for (const auto& platform : platforms) {
			SDL_SetRenderDrawColor(renderer, 100, 250, 0, 0);
			SDL_RenderFillRect(renderer, &platform.hitbox);
		}
		for (size_t i = 0; i < guns.size(); ) {
			if (guns[i].hitbox.x > 800 || guns[i].hitbox.x < 0) {
				guns.erase(guns.begin() + i);  // Xóa phần tử nếu ra khỏi giới hạn
			}
			else {
				guns[i].move();  // Cập nhật vị trí của gun

				// Vẽ lại gun bằng SDL
				SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);  // Màu xám
				SDL_RenderFillRect(renderer, &guns[i].hitbox);  // Vẽ hình chữ nhật

				i++;  // Chỉ tăng i nếu không xóa phần tử
			}
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0; 
}