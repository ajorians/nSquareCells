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
         int bShouldQuit = 0;
         CreateMainMenu(&pMenu);
         while(MainMenuLoop(pMenu)){}
         bShouldQuit = MainMenuShouldQuit(pMenu);
         FreeMainMenu(&pMenu);

         if( bShouldQuit )
            break;
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
         int bShouldQuit = 0;
         CreateGame(&pGame, LEVEL_33);
         while(GameLoop(pGame)){}
         bShouldQuit = GameShouldQuit(pGame);
         FreeGame(pGame);

         if( bShouldQuit )
            break;
      }
   }

   return 0;
}
