#pragma once
#include "raylib/raylib.h"
#include <vector>
#include <cstdint>

class Player {
  
private:
  float moveSpeed;      
  float jumpVelocity;   
  Vector2 velocity;     
  
  float gravity;        
  float maxFallSpeed;   

  float startY;
  float maxJumpHeight;
  
  bool isGrounded;      
  bool onGround;        
  
  std::vector<Rectangle> collisionRecs;
  
  void HandleInput();
  void HandleCollisions();

public:

  Player(uint8_t x, uint8_t y);
  
  void Init(std::vector<Vector2> CollisionLayer);
  void Update();
  void Draw();
  
  Vector2 position;
  Rectangle collisionShape;
  Texture2D texture;
};
