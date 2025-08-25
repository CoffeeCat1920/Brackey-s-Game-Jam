#pragma once

#include "map/tileSet.hpp"
#include "map/tileMapLayer.h"
#include <cstdint>
#include <memory>
#include <vector>


class TileMap {
  
private:

  std::filesystem::path jsonPath; 
  std::filesystem::path tileSetPath;

  std::unique_ptr<TileSet> tileSet;

  std::vector<TileMapLayer> tileMapLayer;

  uint8_t width, height;

public:

  TileMap(std::filesystem::path jsonPath);

  void Init();
  void Draw();
  std::vector<Vector2> GetCollisionRects();
};
