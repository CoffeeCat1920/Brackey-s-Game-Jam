#include "tileMap.hpp"
#include "map/tileSet.hpp"
#include "nlohmann/json_utils.hpp"
#include "raylib/raylib.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>

TileMap::TileMap(std::filesystem::path jsonPath) : 
  jsonPath(jsonPath) 
{
  std::ifstream file(jsonPath);
  if (!file.is_open()) {
    throw std::runtime_error("ERROR: Couldn't find Tileset [" + jsonPath.string() + "]\n");
  }

  json mapData;
  file >> mapData;

  width = mapData["width"]; 
  height = mapData["height"];

  std::string tileSetSource = mapData["tilesets"][0]["source"].get<std::string>().replace(0, 2, "./assets/");

  tileSetPath = std::filesystem::path(tileSetSource);

  if (mapData.contains("layers")) {
    for ( const auto& layerData : mapData["layers"]) {
      if (layerData["type"] == "tilelayer") {
        TileMapLayer layer; 
        layer.id = layerData["id"];
        layer.width = layerData["width"];
        layer.height = layerData["height"];
        layer.offsetX = layerData["x"];
        layer.offsetY = layerData["y"];

        if (layerData.contains("data")) {
          layer.tiles = layerData["data"].get<std::vector<uint16_t>>();
        }

        if (layer.tiles.size() != layer.width * layer.height) {
          throw std::runtime_error("Layer data size mismatch for layer" + std::to_string(layer.id));
        }

        tileMapLayer.push_back(layer);
      }
    }
  }

}

std::vector<Vector2> TileMap::GetCollisionRects() {
  std::vector<Vector2> vecs; 

  TileMapLayer layer = tileMapLayer[0];
  
  for (int x = 0; x < layer.width; x ++) {
    for (int y = 0; y < layer.height; y++) {
      uint8_t tileId = layer.tiles[y * width + x];
      if (tileId > 0) {
        vecs.push_back(Vector2{(float)x, (float)y});
      }
    }
  }

  return vecs;
}

void TileMap::Init() {
  this->tileSet = std::make_unique<TileSet>(tileSetPath);
}

void TileMap::Draw() {
  TileMapLayer layer = tileMapLayer[0];

  for (int x = 0; x < layer.width; x ++) {
    for (int y = 0; y < layer.height; y++) {
      uint8_t tileId = layer.tiles[y * width + x];
      tileSet->DrawTile(tileId, x, y);
    }
  }
}
