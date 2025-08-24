#include "./include/raylib.h"

int main (int argc, char *argv[]) {
  
  InitWindow( 64*5 , 64*5, "Animation Test");

  while ( !WindowShouldClose() )
  { 

    BeginDrawing();

    ClearBackground(GRAY);

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
