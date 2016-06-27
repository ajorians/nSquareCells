#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "MainMenu.h"
#include "StarDrawer.h"

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);
   pMenu->m_eChoice = Play;
   pMenu->m_nLevelNum = nLevelNum >= 1 ? nLevelNum : 1;

   pMenu->m_pBackground = NULL;
   CreateBackground(&pMenu->m_pBackground, pConfig);

   pMenu->m_pConfig = pConfig;
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   struct MainMenu* pMenu = *ppMenu;
   FreeBackground(&pMenu->m_pBackground);

   pMenu->m_pConfig = NULL;//Does not own

   free(*ppMenu);
   *ppMenu = NULL;
}

void DrawMenuPieces(struct MainMenu* pMenu, Gc* pgc)
{
   const int nDimensionSize = 6;

   int nPieceWidth = SCREEN_WIDTH/nDimensionSize;
   int nPieceHeight = (SCREEN_HEIGHT-60)/nDimensionSize;
   int nMinPieceDim = nPieceWidth > nPieceHeight ? nPieceHeight : nPieceWidth;

   int nWidthNeeded = nDimensionSize*nMinPieceDim;
   int nHeightNeeded = nDimensionSize*nMinPieceDim;
   int x = (SCREEN_WIDTH - nWidthNeeded)/2;
   int y = (SCREEN_HEIGHT - nHeightNeeded)/2;

   for(int nX=0; nX<nDimensionSize; nX++) {
      for(int nY=0; nY<nDimensionSize; nY++) {
         int nPieceX = x + nX*nMinPieceDim;
         int nPieceY = y + nY*nMinPieceDim;

         int nLevelNum = nY*nDimensionSize + nX + 1/*0-based to 1-based*/;

         int bCurrentRow = 0;
         if( pMenu->m_eChoice == Play ) {
            if( pMenu->m_nLevelNum >= 1 && pMenu->m_nLevelNum <= 6 && nLevelNum >= 1 && nLevelNum <= 6 ) {
               bCurrentRow = 1;
            } else if( pMenu->m_nLevelNum >= 7 && pMenu->m_nLevelNum <= 12 && nLevelNum >= 7 && nLevelNum <= 12 ) {
               bCurrentRow = 1;
            } else if( pMenu->m_nLevelNum >= 13 && pMenu->m_nLevelNum <= 18 && nLevelNum >= 13 && nLevelNum <= 18 ) {
               bCurrentRow = 1;
            } else if( pMenu->m_nLevelNum >= 19 && pMenu->m_nLevelNum <= 24 && nLevelNum >= 19 && nLevelNum <= 24 ) {
               bCurrentRow = 1;
            } else if( pMenu->m_nLevelNum >= 25 && pMenu->m_nLevelNum <= 30 && nLevelNum >= 25 && nLevelNum <= 30 ) {
               bCurrentRow = 1;
            } else if( pMenu->m_nLevelNum >= 31 && nLevelNum >= 31 ) {
               bCurrentRow = 1;
            }
         }
         if( bCurrentRow == 1 ) {
            gui_gc_setColorRGB(*pgc, 0, 220, 0);
         } else {
            gui_gc_setColorRGB(*pgc, 0x59, 0x59, 0x59);
         }
         gui_gc_fillRect(*pgc, nPieceX + 2, nPieceY + 2, nMinPieceDim-3, nMinPieceDim-3);

         if( pMenu->m_eChoice == Play && pMenu->m_nLevelNum == nLevelNum ) {
            gui_gc_setColorRGB(*pgc, 255, 0, 0);

            gui_gc_drawRect(*pgc, nPieceX, nPieceY, nMinPieceDim, nMinPieceDim);
         }

         gui_gc_setColorRGB(*pgc, 255, 255, 255);
         char buf[8];
         sprintf(buf, "%d", nLevelNum);
         char buffer[16];
         ascii2utf16(buffer, buf, 16);

         int nHeightSpaceDesired = gui_gc_getStringSmallHeight(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
      int nWidthSpaceDesired = gui_gc_getStringWidth(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);

         int nXOffset = nMinPieceDim/2 - nWidthSpaceDesired/2;
         int nYOffset = 2;

         int nPosX = nPieceX + nXOffset;
         int nPosY = nPieceY + nYOffset;

         gui_gc_drawString(*pgc, buffer, nPosX, nPosY, GC_SM_TOP);

         int nStars = 0;
         GetBeatLevel(pMenu->m_pConfig, nLevelNum-1, &nStars);
         int a = nMinPieceDim/3;
         for(int nStarsToDraw=0; nStarsToDraw<nStars; nStarsToDraw++) {
            DrawStar(pgc, nPieceX+nStarsToDraw*a+a/2+1, nPosY+nMinPieceDim-a, a);
         }
      }
   }
}

int MainMenuLoop(struct MainMenu* pMenu)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   DrawBackground(pMenu->m_pBackground, &gc);

   DrawMenuPieces(pMenu, &gc);

   gui_gc_setColorRGB(gc, 0, 0, 0);

   char* strMenu = "n\0S\0q\0u\0a\0r\0e\0C\0e\0l\0l\0s\0\0";
   gui_gc_drawString(gc, strMenu, 110, 5, GC_SM_TOP);

   char* strOptions = "O\0p\0t\0i\0o\0n\0s\0\0";
   gui_gc_drawString(gc, strOptions, 75, SCREEN_HEIGHT-30, GC_SM_TOP);

   char* strHelp = "H\0e\0l\0p\0\0";
   gui_gc_drawString(gc, strHelp, SCREEN_WIDTH-115, SCREEN_HEIGHT-30, GC_SM_TOP);

   if( pMenu->m_eChoice == Options ) {
      gui_gc_setColorRGB(gc, 255, 0, 0);
      gui_gc_drawRect(gc, 73, SCREEN_HEIGHT-30, 60, 20);
   }
   else if( pMenu->m_eChoice == Help ) {
      gui_gc_setColorRGB(gc, 255, 0, 0);
      gui_gc_drawRect(gc, SCREEN_WIDTH-117, SCREEN_HEIGHT-30, 45, 20);
   }

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);

   if( isKeyPressed(KEY_NSPIRE_ESC) ) {
      pMenu->m_eChoice = Quit;
      return 0;
   }
   if( isKeyPressed(KEY_NSPIRE_UP) && ( pMenu->m_eChoice == Options || pMenu->m_eChoice == Help ) ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Play;
   }
   else if( isKeyPressed(KEY_NSPIRE_UP) && pMenu->m_eChoice == Play && pMenu->m_nLevelNum > 6 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum -= 6;
   }
   else if( isKeyPressed(KEY_NSPIRE_DOWN) && pMenu->m_eChoice == Play && pMenu->m_nLevelNum >= 31 && pMenu->m_nLevelNum <= 36 ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Options;
   }
   else if( isKeyPressed(KEY_NSPIRE_DOWN) && pMenu->m_eChoice == Play && pMenu->m_nLevelNum < 31 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum += 6;
   }

   if( isKeyPressed(KEY_NSPIRE_ENTER) ) {
      wait_no_key_pressed();
      return 0;
   }

   if( isKeyPressed(KEY_NSPIRE_LEFT) && pMenu->m_eChoice == Play && pMenu->m_nLevelNum > 1 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum--;
   }
   else if( isKeyPressed(KEY_NSPIRE_LEFT) && pMenu->m_eChoice == Help ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Options;
   }
   else if( isKeyPressed(KEY_NSPIRE_RIGHT) && pMenu->m_eChoice == Play && pMenu->m_nLevelNum < 36 ) {
      wait_no_key_pressed();
      pMenu->m_nLevelNum++;
   }
   else if( isKeyPressed(KEY_NSPIRE_RIGHT) && pMenu->m_eChoice == Options ) {
      wait_no_key_pressed();
      pMenu->m_eChoice = Help;
   }
   
   return 1;
}

int MainMenuShouldQuit(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Quit;
}

int MainMenuShowOptions(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Options;
}

int MainMenuShowHelp(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Help;
}

int MainMenuGetLevelNum(struct MainMenu* pMenu)
{
   return pMenu->m_nLevelNum;
}

