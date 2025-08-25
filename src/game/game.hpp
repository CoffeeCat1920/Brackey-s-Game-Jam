#pragma once

#include "map/tileMap.hpp"
#include "player/player.hpp"

class Game {
  
private:
  
  TileMap tileMap; 
  Player player;
  
public:

  Game();

  void Init();
  void Update();
  void Draw();
};
