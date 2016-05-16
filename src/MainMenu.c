#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "MainMenu.h"

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);
   pMenu->m_eChoice = Play;
   pMenu->m_nLevelNum = nLevelNum >= 1 ? nLevelNum : 1;
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   free(*ppMenu);
   *ppMenu = NULL;
}

int MainMenuLoop(struct MainMenu* pMenu)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   gui_gc_setColorRGB(gc, 250, 250, 250);
   gui_gc_fillRect(gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   gui_gc_setColorRGB(gc, 0, 0, 0);

   char* strMenu = "P\0l\0a\0y\0\0";
   gui_gc_drawString(gc, strMenu, 50, 50, GC_SM_TOP);

   char* strOptions = "O\0p\0t\0i\0o\0n\0s\0\0";
   gui_gc_drawString(gc, strOptions, 50, 70, GC_SM_TOP);

   char buf[8];
   char buffer[16];
   sprintf(buf, "%d", pMenu->m_nLevelNum);
   ascii2utf16(buffer, buf, 16);
   gui_gc_drawString(gc, buffer, 160, 50, GC_SM_TOP);

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
   }

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);

   if( isKeyPressed(KEY_NSPIRE_ESC) ) {
      pMenu->m_eChoice = Quit;
      return 0;
   }
   if( isKeyPressed(KEY_NSPIRE_UP) && pMenu->m_eChoice == Options ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Play;
   }
   else if( isKeyPressed(KEY_NSPIRE_DOWN) && pMenu->m_eChoice == Play ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Options;
   }

   if( isKeyPressed(KEY_NSPIRE_ENTER) ) {
      wait_no_key_pressed();
      return 0;
   }

   if( isKeyPressed(KEY_NSPIRE_LEFT) && pMenu->m_nLevelNum > 1 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum--;
   }
   else if( isKeyPressed(KEY_NSPIRE_RIGHT) && pMenu->m_nLevelNum < 36 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum++;
   }
   
   return 1;
}

int MainMenuShouldQuit(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Quit;
}

int MainMenuGetLevelNum(struct MainMenu* pMenu)
{
   return pMenu->m_nLevelNum;
}

