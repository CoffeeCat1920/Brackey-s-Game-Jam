#include "game/game.hpp"
#include "include/core/colors.hpp"
#include "include/core/settings.hpp"
#include "raylib/raylib.h"

int main () {

  InitWindow( BLOCK * BOARD_WIDTH, BLOCK * BOARD_HEIGHT, "Risk it For The Biscuit");

  Game game;

  game.Init();

  while ( !WindowShouldClose() )
  { 

    game.Update();

    BeginDrawing();

    game.Draw();

    ClearBackground(GRUVBOX_DARK0);

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
