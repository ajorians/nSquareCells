#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"

void CreateGame(struct Game** ppGame)
{
   *ppGame = malloc(sizeof(struct Game));
}

void FreeGame(struct Game** ppGame)
{
   free(*ppGame);
   *ppGame = NULL;
}

int GameLoop(struct Game* pGame)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   gui_gc_setColorRGB(gc, 0, 250, 250);
   gui_gc_fillRect(gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   gui_gc_setColorRGB(gc, 0, 0, 0);

   /*char* strMenu = "P\0l\0a\0y\0\0";
   gui_gc_drawString(gc, strMenu, 50, 50, GC_SM_TOP);

   char* strOptions = "O\0p\0t\0i\0o\0n\0s\0\0";
   gui_gc_drawString(gc, strOptions, 50, 70, GC_SM_TOP);

   if( pMenu->m_eChoice == Play ) {
      gui_gc_drawLine(gc, 50, 50, 100, 50);
      gui_gc_drawLine(gc, 100, 50, 100, 70);
      gui_gc_drawLine(gc, 50, 50, 50, 70);
      gui_gc_drawLine(gc, 50, 70, 100, 70);
   }
   else if( pMenu->m_eChoice == Options ) {
      gui_gc_drawLine(gc, 50, 70, 100, 70);
      gui_gc_drawLine(gc, 100, 70, 100, 90);
      gui_gc_drawLine(gc, 50, 70, 50, 90);
      gui_gc_drawLine(gc, 50, 90, 100, 90);
   }*/

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);

   if( isKeyPressed(KEY_NSPIRE_ESC) )
      return 0;
   /*if( isKeyPressed(KEY_NSPIRE_UP) && pMenu->m_eChoice == Options )
      pMenu->m_eChoice = Play;
   else if( isKeyPressed(KEY_NSPIRE_DOWN) && pMenu->m_eChoice == Play )
      pMenu->m_eChoice = Options;*/
   
   return 1;
}

/*int MainMenuShouldQuit(struct MainMenu* pMenu)
{
   return 1;
}*/

