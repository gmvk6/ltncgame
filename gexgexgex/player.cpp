#include<iostream>
#include<SDL.h>
#include<vector>
#include "Player.hpp"
using namespace std;

Player::Player(int x, int y, int width, int height) {
    velocityY = 0;
    isOnGround = false;
    canFallThrough = false;
    dx = 0;
    dy = 0; 
    dir = 1;
    add = 25;
    hitbox = { x - width / 2 , y - height / 2 , width , height};
    ground = { x - width / 2 , y - height / 2 , width , 5 };
    hurtbox = { hitbox.x ,hitbox.y , hitbox.w , hitbox.h };
}

void Player::jumb() {
    if (isOnGround) {
        velocityY = -30;
        isOnGround = false;
    }
}

void Player::move(int x, int y, const vector<Entity>& platforms) {
    if (dir == -1) {
        add = -50;
        hurtbox.x = hitbox.x - 50;
    }
    else {
        add = 50;
        hurtbox.x = hitbox.x + 50;
    }
    int newX = hitbox.x + x;
    int newY = hitbox.y + y;

    SDL_Rect futureHitbox = { newX, hitbox.y, hitbox.w, hitbox.h };
    for (const auto& platform : platforms) {
        if (SDL_HasIntersection(&futureHitbox, &platform.hitbox)) {
            x = 0;  // Ngăn chặn di chuyển ngang nếu có va chạm
            break;
        }
    }

    hitbox.x += x;
    hitbox.y += y;
    hurtbox.x += x;
    hurtbox.y += y;
}

bool Player::checkCollision(const vector<SDL_Rect>& platforms) {
    for (const auto& platform : platforms) {
        if (SDL_HasIntersection(&hitbox, &platform)) {
            return true;
        }
    }
    return false;
}

void Player::applyGravity(const vector<Entity>& platforms) {
    velocityY += 2;
    
    hitbox.y += velocityY;
    hurtbox.y += velocityY;
    ground.y += velocityY;
    //velocityY = velocityY >= 50 ? 50 : velocityY;
    //cout << hitbox.y << endl;

    for (const auto& platform : platforms) {
        if (SDL_HasIntersection(&hitbox, &platform.hitbox)) {
     
            if (velocityY < 0) continue;
            if (canFallThrough) {
                continue;
            }
            hitbox.y -= velocityY;
            hurtbox.y -= velocityY;
            ground.y -= velocityY;
            velocityY = 0;
            isOnGround = true;
            return;
        }
    }
    isOnGround = false;
}

void Player::fall() {
    //if (isOnGround) {
    //    //canFallThrough = true;  // Bắt đầu rơi xuyên qua platform
    //    velocityY += 5;          // Giữ nguyên tốc độ rơi tự nhiên
    //    //isOnGround = false;     // Đánh dấu là đang rơi
    //}
}
