#pragma once

#include "raylib/raylib.h"
#include <cstdint>
#include <vector>

class Player {
  
private:
  Texture2D texture;

  Vector2 position;
  Vector2 direction;
  
  float velocity;
  float gravity;

  std::vector<Rectangle> CollisionRecs;

public:

  Player(uint8_t x, uint8_t y);  

  void Init(std::vector<Vector2> CollisionLayer);
  void Update();
  void Draw();
};
