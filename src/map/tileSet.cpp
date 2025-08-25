#include "tileSet.hpp"
#include "nlohmann/json_utils.hpp"
#include "raylib/raylib.h"
#include "core/settings.hpp"

#include <cstdint>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

Tile::Tile(uint16_t id, uint8_t x, uint8_t y) : 
  id(id), 
  x(x), 
  y(y) {}

TileSet::TileSet(std::filesystem::path jsonPath) : 
  jsonPath(jsonPath) 
{
  std::ifstream file(jsonPath);
  if (!file.is_open()) {
    throw std::runtime_error("ERROR: Couldn't find Tileset [" + jsonPath.string() + "]\n");
  }

  json mapData;
  file >> mapData;

  atlasPath = std::filesystem::path(
      mapData["image"].get<std::string>()
  );
  atlasPath = std::filesystem::path("./assets/tileSet") / atlasPath;
  if (!std::filesystem::exists(atlasPath)) {
      throw std::runtime_error("Texture file does not exist: " + atlasPath.string());
  }

  atlas = LoadTexture(atlasPath.c_str());

  atlasWidth = mapData["imagewidth"];
  atlasHeight = mapData["imageheight"];

  tileWidth = mapData["tilewidth"];
  tileHeight = mapData["tileheight"];

  uint16_t tileCount = mapData["tilecount"];
  tiles.reserve(tileCount);

  uint16_t id = 0;

  for (int x = 0; x < atlasWidth; x += tileWidth) {
    for (int y = 0; y < atlasHeight; y += tileHeight) {
      tiles.push_back( std::make_shared<Tile>(id, x, y) );
      id++;
    } 
  }
}

void TileSet::DrawTile(uint16_t id, uint32_t x, uint32_t y) {
  if (id <= 0) {
    return;
  }

  --id;
  if (id >= tiles.size()) {
    throw std::out_of_range("Invalid tile ID: " + std::to_string(id));
    return;
  }

  std::shared_ptr<Tile> tile = tiles[id];
  Rectangle rec = Rectangle{(float)tile->x, (float)tile->y, (float)tileWidth, (float)tileHeight};   
  Vector2 pos = Vector2{(float)x * BLOCK, (float)y * BLOCK};
  DrawTextureRec(atlas, rec, pos, WHITE);
}
