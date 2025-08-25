#include "game.hpp"
#include "map/tileMap.hpp"
#include "player/player.hpp"

Game::Game() :
  tileMap("./assets/tileMap/tileMap.json"),
  player(2, 2) 
{}


void Game::Init() {
  tileMap.Init();
  player.Init(tileMap.GetCollisionRects());
} 

void Game::Update() {
  player.Update();
}

void Game::Draw() {
  tileMap.Draw();
  player.Draw();
}
