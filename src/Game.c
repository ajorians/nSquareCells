#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"
#include "Metrics.h"
#include "Piece.h"
#include "Selector.h"
#include "Indicators.h"

void CreateGame(struct Game** ppGame, const char* pstrLevelData)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   SquareLibCreate(&(pGame->m_Square), pstrLevelData);

   pGame->m_gc = gui_gc_global_GC();

   gui_gc_begin(pGame->m_gc);
   pGame->m_pMetrics = NULL;
   CreateMetrics(&pGame->m_pMetrics, pGame->m_Square, &pGame->m_gc);

   int nWidth = GetSquareWidth(pGame->m_Square);
   int nHeight = GetSquareHeight(pGame->m_Square);
   int nNumPtrs = nWidth * nHeight;
   pGame->m_apPieces = malloc(nNumPtrs*sizeof(struct Piece));
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         CreatePiece(pPiece, x, y, pGame->m_Square, pGame->m_pMetrics);
      }
   }

   pGame->m_pSelector = NULL;
   CreateSelector(&pGame->m_pSelector, pGame->m_Square, pGame->m_pMetrics);

   pGame->m_pIndicators = NULL;
   CreateIndicators(&pGame->m_pIndicators, pGame->m_Square, pGame->m_pMetrics);

   pGame->m_bShouldQuit = 0;
}

void FreeGame(struct Game** ppGame)
{
   struct Game* pGame = *ppGame;
   FreeMetrics(&pGame->m_pMetrics);
   pGame->m_pMetrics = NULL;

   int nWidth = GetSquareWidth(pGame->m_Square);
   int nHeight = GetSquareHeight(pGame->m_Square);
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         FreePiece(pPiece);
      }
   }
   free(pGame->m_apPieces);

   FreeSelector(&pGame->m_pSelector);
   FreeIndicators(&pGame->m_pIndicators);

   gui_gc_finish(pGame->m_gc);

   free(pGame);
   *ppGame = NULL;
}

void DrawBoard(struct Game* pGame)
{
   gui_gc_setColorRGB(pGame->m_gc, 0, 250, 250);
   gui_gc_fillRect(pGame->m_gc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   int nWidth = GetSquareWidth(pGame->m_Square);
   int nHeight = GetSquareHeight(pGame->m_Square);

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
   IndicatorsDraw(pGame->m_pIndicators, &pGame->m_gc);

   //Draw pieces
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         PieceDraw(pPiece, &pGame->m_gc);
      }
   }

   //Draw selector
   SelectorDraw(pGame->m_pSelector, &pGame->m_gc);

   //Draw remaining
   char buffer[32];
   sprintf(buffer, "%d to remove", GetSquaresRemaining(pGame->m_Square));
   char bufferUnicode[32];
   ascii2utf16(bufferUnicode, buffer, 32);
   gui_gc_setColorRGB(pGame->m_gc, 0, 0, 0);
   gui_gc_drawString(pGame->m_gc, bufferUnicode, 10, 10, GC_SM_TOP);

   gui_gc_blit_to_screen(pGame->m_gc);
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

   int nSelectionX = pGame->m_pSelector->m_nSelectionX;
   int nSelectionY = pGame->m_pSelector->m_nSelectionY;
   int nDestroyed = 0;
   if( IsKeyPressed(KEY_NSPIRE_ESC) ) {
      pGame->m_bShouldQuit = 0;//Could change to completly close program
      return 0;
   }
   else if( IsKeyPressed(KEY_NSPIRE_LEFT) )
      SelectorMove(pGame->m_pSelector, Sel_Left);
   else if( IsKeyPressed(KEY_NSPIRE_RIGHT) )
      SelectorMove(pGame->m_pSelector, Sel_Right);
   else if( IsKeyPressed(KEY_NSPIRE_UP) )
      SelectorMove(pGame->m_pSelector, Sel_Up);
   else if( IsKeyPressed(KEY_NSPIRE_DOWN) )
      SelectorMove(pGame->m_pSelector, Sel_Down);
   else if( IsKeyPressed(KEY_NSPIRE_CTRL) ) {
      IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED )
         DestroySquare(pGame->m_Square, nSelectionX, nSelectionY);
   }
   else if( IsKeyPressed(KEY_NSPIRE_SHIFT) ) {
      IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED )
         ToggleSquareMark(pGame->m_Square, nSelectionX, nSelectionY);
   }

   if( IsSquareGameOver(pGame->m_Square) == SQUARELIB_GAMEOVER )
      return 0;
   
   return 1;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

