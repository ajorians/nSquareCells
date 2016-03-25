#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"

void CreateGame(struct Game** ppGame, const char* pstrLevelData)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   SquareLibCreate(&(pGame->m_Square), pstrLevelData);
   pGame->m_nSelectionX = pGame->m_nSelectionY = 0;
   pGame->m_bShouldQuit = 0;
}

void FreeGame(struct Game** ppGame)
{
   free(*ppGame);
   *ppGame = NULL;
}

void DrawBoard(struct Game* pGame)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   gui_gc_setColorRGB(gc, 0, 250, 250);
   gui_gc_fillRect(gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   int nWidth = GetSquareWidth(pGame->m_Square);
   int nHeight = GetSquareHeight(pGame->m_Square);

   int nMaxColIndicators = 0;
   for(int x=0; x<nWidth; x++) {
      int nIndicators = GetNumSquareIndicatorsForCol(pGame->m_Square, x);
      if( nIndicators > nMaxColIndicators )
         nMaxColIndicators = nIndicators;
   }

   int nMaxRowIndicators = 0;
   for(int y=0; y<nHeight; y++) {
      int nIndicators = GetNumSquareIndicatorsForRow(pGame->m_Square, y);
      if( nIndicators > nMaxRowIndicators )
         nMaxRowIndicators = nIndicators;
   }

   int nSpotsNeededHorizontally = nWidth + nMaxRowIndicators;
   int nSpotsNeededVertically = nHeight + nMaxColIndicators;

   int nPieceWidth = SCREEN_WIDTH / nSpotsNeededHorizontally;
   int nPieceHeight = SCREEN_HEIGHT / nSpotsNeededVertically;
   int nPieceDim = nPieceWidth < nPieceHeight ? nPieceWidth : nPieceHeight;

   int nLeft = (SCREEN_WIDTH - (nPieceDim * nSpotsNeededHorizontally))/2;
   int nTop = (SCREEN_HEIGHT - (nPieceDim * nSpotsNeededVertically))/2;

   int nLeftBoard = nLeft + nMaxColIndicators*nPieceDim;
   int nTopBoard = nTop + nMaxRowIndicators*nPieceDim;

   //Draw outlines
#if 0
   gui_gc_setColorRGB(gc, 0, 0, 0);
   for(int x=0; x<=nWidth; x++) {
      gui_gc_drawLine(gc, nLeftBoard + x*nPieceDim, nTopBoard, nLeftBoard + x*nPieceDim, nTopBoard + nHeight*nPieceDim);
   }

   for(int y=0; y<=nHeight; y++) {
      gui_gc_drawLine(gc, nLeftBoard, nTopBoard + y*nPieceDim, nLeftBoard + nWidth*nPieceDim, nTopBoard + y*nPieceDim);
   }
#endif

   //Draw indicators
   gui_gc_setColorRGB(gc, 0, 0, 0);
   for(int x=0; x<nWidth; x++) {
      int arr[8] = {0};
      int nIndicators = GetSquareIndicatorsForCol(pGame->m_Square, x, arr);
      int nIndicatorOffset = nMaxColIndicators - nIndicators;
      enum IndicatorType eType;
      GetSquareIndicatorTypeCol(pGame->m_Square, x, &eType);
      for(int i=0; i<nIndicators; i++) {
         char buf[8];
         if( eType == FullNumbers ) 
            sprintf(buf, "[%d]", arr[i]);
         else
            sprintf(buf, "%d", arr[i]);
         char buffer[16];
         ascii2utf16(buffer, buf, 16);
         int nSpaceDesired = gui_gc_getStringWidth(gc, Regular9, buf, 0, 1);
         gui_gc_drawString(gc, buffer, nLeftBoard + x*nPieceDim + (nPieceDim-nSpaceDesired)/2, nTop + (i+nIndicatorOffset)*nPieceDim, GC_SM_TOP);
      }
   }

   for(int y=0; y<nHeight; y++) {
      int arr[8] = {0};
      int nIndicators = GetSquareIndicatorsForRow(pGame->m_Square, y, arr);
      int nIndicatorOffset = nMaxRowIndicators - nIndicators;
      enum IndicatorType eType;
      GetSquareIndicatorTypeRow(pGame->m_Square, y, &eType);
      for(int i=0; i<nIndicators; i++) {
         char buf[8];
         if( eType == FullNumbers )
            sprintf(buf, "[%d]", arr[i]);
         else
            sprintf(buf, "%d", arr[i]);
         char buffer[16];
         ascii2utf16(buffer, buf, 16);
         int nSpaceDesired = gui_gc_getStringHeight(gc, Regular9, buf, 0, 1);
         gui_gc_drawString(gc, buffer, nLeft + (i+nIndicatorOffset)*nPieceDim, nTopBoard + y*nPieceDim + (nPieceDim-nSpaceDesired)/2, GC_SM_TOP);
      }
   }

   //Draw pieces
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         int nPieceX = nLeftBoard + x*nPieceDim,
             nPieceY = nTopBoard + y*nPieceDim;

         int nDestroyed = 0, nMarked = 0;
         IsSquareDestroyed(pGame->m_Square, x, y, &nDestroyed);
         if( nDestroyed == SQUARELIB_DESTROYED ) {
            int nSqSize = nPieceDim / 2;
            gui_gc_setColorRGB(gc, 127, 127, 127);
            gui_gc_fillRect(gc, nPieceX + nSqSize/2, nPieceY + nSqSize/2, nSqSize, nSqSize);
            continue;
         }

         gui_gc_setColorRGB(gc, 255, 255, 255);
         gui_gc_drawRect(gc, nPieceX + 1, nPieceY + 1, nPieceDim-2, nPieceDim-2);

         gui_gc_setColorRGB(gc, 0, 220, 0);
         gui_gc_fillRect(gc, nPieceX + 2, nPieceY + 2, nPieceDim-3, nPieceDim-3);

         IsSquareMarked(pGame->m_Square, x, y, &nMarked);
         if( nMarked == SQUARELIB_MARKED ) {
            gui_gc_setColorRGB(gc, 0, 175, 0);
            gui_gc_fillRect(gc, nPieceX + 2, nPieceY + nPieceDim/2 + 2, nPieceDim-3, nPieceDim/2-3);

            gui_gc_setColorRGB(gc, 255, 255, 255);
            gui_gc_fillRect(gc, nPieceX + nPieceDim - 12, nPieceY + 4, 6, 6);
         }
      }
   }

   //Draw selector
   gui_gc_setColorRGB(gc, 255, 0, 0);
   int nSelectionX = nLeftBoard + pGame->m_nSelectionX * nPieceDim,
       nSelectionY = nTopBoard + pGame->m_nSelectionY * nPieceDim;
   gui_gc_drawLine(gc, nSelectionX, nSelectionY, nSelectionX + nPieceDim, nSelectionY);
   gui_gc_drawLine(gc, nSelectionX, nSelectionY, nSelectionX, nSelectionY + nPieceDim);
   gui_gc_drawLine(gc, nSelectionX + nPieceDim, nSelectionY, nSelectionX + nPieceDim, nSelectionY + nPieceDim);
   gui_gc_drawLine(gc, nSelectionX, nSelectionY + nPieceDim, nSelectionX + nPieceDim, nSelectionY + nPieceDim);

   //Draw remaining
   char buffer[32];
   sprintf(buffer, "%d to remove", GetSquaresRemaining(pGame->m_Square));
   char bufferUnicode[32];
   ascii2utf16(bufferUnicode, buffer, 32);
   gui_gc_setColorRGB(gc, 0, 0, 0);
   gui_gc_drawString(gc, bufferUnicode, 10, 10, GC_SM_TOP);

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);
}

int IsKeyPressed(const t_key key){
   if( !isKeyPressed(key) )
      return 0;

   while( isKeyPressed(key) ){}

   return 1;
}

int GameLoop(struct Game* pGame)
{
   DrawBoard(pGame);

   int nDestroyed = 0;
   if( IsKeyPressed(KEY_NSPIRE_ESC) ) {
      pGame->m_bShouldQuit = 0;//Could change to completly close program
      return 0;
   }
   else if( IsKeyPressed(KEY_NSPIRE_LEFT) && pGame->m_nSelectionX > 0 )
      pGame->m_nSelectionX--;
   else if( IsKeyPressed(KEY_NSPIRE_RIGHT) && pGame->m_nSelectionX < (GetSquareWidth(pGame->m_Square)-1) )
      pGame->m_nSelectionX++;
   else if( IsKeyPressed(KEY_NSPIRE_UP) && pGame->m_nSelectionY > 0 )
      pGame->m_nSelectionY--;
   else if( IsKeyPressed(KEY_NSPIRE_DOWN) && pGame->m_nSelectionY < (GetSquareHeight(pGame->m_Square)-1) )
      pGame->m_nSelectionY++;
   else if( IsKeyPressed(KEY_NSPIRE_CTRL) ) {
      IsSquareDestroyed(pGame->m_Square, pGame->m_nSelectionX, pGame->m_nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED )
         DestroySquare(pGame->m_Square, pGame->m_nSelectionX, pGame->m_nSelectionY);
   }
   else if( IsKeyPressed(KEY_NSPIRE_SHIFT) ) {
      IsSquareDestroyed(pGame->m_Square, pGame->m_nSelectionX, pGame->m_nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED )
         ToggleSquareMark(pGame->m_Square, pGame->m_nSelectionX, pGame->m_nSelectionY);
   }

   if( IsSquareGameOver(pGame->m_Square) == SQUARELIB_GAMEOVER )
      return 0;
   
   return 1;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

