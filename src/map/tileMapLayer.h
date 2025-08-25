#pragma once

#include <cstdint>
#include <vector>

struct TileMapLayer {
  uint8_t id;

  std::vector<uint16_t> tiles;
  uint8_t width;
  uint8_t height;

  uint8_t offsetX;
  uint8_t offsetY;

};
