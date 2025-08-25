#include "player.hpp"
#include "core/colors.hpp"
#include "core/settings.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <cstdint>

Player::Player(uint8_t x, uint8_t y) : 
  position(Vector2{(float)x, (float)y}) 
{
  collisionShape = Rectangle{(position.x * BLOCK) - 12, (position.y * BLOCK) - 12, BLOCK - 24, BLOCK - 24};
  texture = LoadTexture("./assets/player/player.png");
  
  moveSpeed = 0.1f;        
  jumpVelocity = -0.4f;    

  startY = 0.0f;
  
  velocity = Vector2{0.0f, 0.0f};  
  gravity = 0.02f;         
  maxFallSpeed = 0.8f;     
  
  isGrounded = false;
  onGround = false;
}

void Player::Init(std::vector<Vector2> CollisionLayer) {
  for (Vector2 pos : CollisionLayer) {
    Rectangle rec = Rectangle{pos.x * BLOCK, pos.y * BLOCK, BLOCK, BLOCK};
    collisionRecs.push_back(rec); 
  } 
}

void Player::Update() {
  HandleInput();
  
  velocity.y += gravity;
  
  if (velocity.y > maxFallSpeed) {
    velocity.y = maxFallSpeed;
  }
  
  position = Vector2Add(position, velocity);
  
  collisionShape.x = position.x * BLOCK + 12;
  collisionShape.y = position.y * BLOCK + 12;
  
  HandleCollisions();
}

void Player::HandleInput() {
  velocity.x = 0.0f;
  
  if (IsKeyDown(KEY_LEFT)) {
    velocity.x = -moveSpeed;  
  }
  if (IsKeyDown(KEY_RIGHT)) {
    velocity.x = moveSpeed;     
  }
  
  if (IsKeyPressed(KEY_Z) && isGrounded) {
    velocity.y = jumpVelocity;
    isGrounded = false;
  }
}

void Player::HandleCollisions() {
  isGrounded = false;
  
  for (const Rectangle& collisionRec : collisionRecs) {
    if (CheckCollisionRecs(collisionShape, collisionRec)) {
      
      float overlapX = std::min(collisionShape.x + collisionShape.width - collisionRec.x,
                               collisionRec.x + collisionRec.width - collisionShape.x);
      float overlapY = std::min(collisionShape.y + collisionShape.height - collisionRec.y,
                               collisionRec.y + collisionRec.height - collisionShape.y);
      
      if (overlapX < overlapY) {
        if (collisionShape.x < collisionRec.x) {
          position.x = (collisionRec.x - collisionShape.width - 12) / BLOCK;
          velocity.x = 0;
        } else {
          position.x = (collisionRec.x + collisionRec.width - 12) / BLOCK;
          velocity.x = 0;
        }
      } else {
        if (collisionShape.y < collisionRec.y) {
          position.y = (collisionRec.y - collisionShape.height - 12) / BLOCK;
          velocity.y = 0;
          isGrounded = true;
        } else {
          position.y = (collisionRec.y + collisionRec.height - 12) / BLOCK;
          velocity.y = 0;
        }
      }
      
      collisionShape.x = position.x * BLOCK + 12;
      collisionShape.y = position.y * BLOCK + 12;
    }
  }
}

void Player::Draw() {
  DrawTexture(texture, position.x * BLOCK, position.y * BLOCK, WHITE);
  DrawRectangleLinesEx(collisionShape, 2.0f, GRUVBOX_GREEN);
  
  // Debug info (optional)
  DrawText(TextFormat("Velocity: %.2f, %.2f", velocity.x, velocity.y), 10, 10, 20, WHITE);
  DrawText(TextFormat("Grounded: %s", isGrounded ? "YES" : "NO"), 10, 40, 20, WHITE);
}
