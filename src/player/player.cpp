#include "player.hpp"
#include "core/settings.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include <cstdint>

Player::Player(uint8_t x, uint8_t y) : 
  position(Vector2{(float)x, (float)y}) 
{
  texture = LoadTexture("./assets/player/player.png");

  velocity = 2.0f;
  gravity = 2.0f;
}

void Player::Init(std::vector<Vector2> CollisionLayer) {
  for ( Vector2 pos : CollisionLayer ) {
    Rectangle rec = Rectangle{pos.x, pos.y, BLOCK, BLOCK};
    CollisionRecs.push_back(rec); 
  } 
}

void Player::Update() {
  float dt = GetFrameTime();
  direction.y = gravity;
  position = Vector2Add(position, Vector2Scale(direction, dt));
}

void Player::Draw() {
  DrawTexture(texture, position.x * BLOCK, position.y * BLOCK, WHITE);
}
