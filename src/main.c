#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Startup.h"
#include "MainMenu.h"
#include "Game.h"

#define LEVEL_33 "SquareCells 1 4 4 0 2 1 2 0 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 2 2 1 0 1 3 1 0 3 3 1 0 \"\""

int main(int argc, char *argv[])
{
   if( argc != 2 ) {
      if( !config_file_already_written() ) {
         write_config_file();
      }
   }

   int nLevelNumber = -1;
   char strLevelData[2048];
   while(1) {
      int bShowHelp = 0, bShowOptions = 0;
      if( argc != 2 ) {
         struct MainMenu* pMenu = NULL;
         CreateMainMenu(&pMenu);
         while(MainMenuLoop(pMenu)){}
         FreeMainMenu(&pMenu);
      }
      else {
      }

      if( bShowOptions ) {
         continue;
      }
      else if( bShowHelp ) {
         continue;
      }
      else {
         struct Game* pGame = NULL;
         CreateGame(&pGame, LEVEL_33);
         while(GameLoop(pGame)){}
         FreeGame(pGame);
      }
      break;
   }

/*
   SquareLib api;
   int x = 0;
   Gc gc = gui_gc_global_GC();

   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return 1;

   while(1) {
      gui_gc_begin(gc);

      gui_gc_setColorRGB(gc, 250, 250, 250);
      gui_gc_fillRect(gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

      gui_gc_setColorRGB(gc, 0, 0, 0);
      gui_gc_fillRect(gc, x, 0, 30, 30);

      gui_gc_blit_to_screen(gc);

      gui_gc_finish(gc);

      if( isKeyPressed(KEY_NSPIRE_LEFT) )
         x -= 10;
      else if( isKeyPressed(KEY_NSPIRE_RIGHT) )
         x += 10;
      else if( isKeyPressed(KEY_NSPIRE_ESC) )
         break;
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return 1;

   wait_key_pressed();
*/
   return 0;
}
