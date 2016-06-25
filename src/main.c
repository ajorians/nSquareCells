#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Startup.h"
#include "MainMenu.h"
#include "Game.h"
#include "Config.h"
#include "Levels.h"

int main(int argc, char *argv[])
{
   if( argc != 2 ) {
      if( !config_file_already_written() ) {
         write_config_file();
      }
   }

   int nLevelNumber = -1;
   char strLevelData[2048];
   struct Config* pConfig = NULL;
   CreateConfig(&pConfig);
   while(1) {
      int bShowHelp = 0, bShowOptions = 0;
      if( argc != 2 ) {
         struct MainMenu* pMenu = NULL;
         int bShouldQuit = 0;
         CreateMainMenu(&pMenu, nLevelNumber, pConfig);
         while(MainMenuLoop(pMenu)){}
         bShouldQuit = MainMenuShouldQuit(pMenu);
         if( bShouldQuit == 0 ) {
            nLevelNumber = MainMenuGetLevelNum(pMenu);
            LevelLoad(strLevelData, nLevelNumber);
         }
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
         CreateGame(&pGame, strLevelData, nLevelNumber, pConfig);
         while(GameLoop(pGame)){}
         bShouldQuit = GameShouldQuit(pGame);
         FreeGame(&pGame);

         if( bShouldQuit )
            break;
      }
   }

   FreeConfig(&pConfig);

   return 0;
}
