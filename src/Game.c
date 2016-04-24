#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"
#include "Metrics.h"
#include "Piece.h"
#include "Selector.h"

void CreateGame(struct Game** ppGame, const char* pstrLevelData)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   SquareLibCreate(&(pGame->m_Square), pstrLevelData);

   pGame->m_pMetrics = NULL;
   CreateMetrics(&pGame->m_pMetrics, pGame->m_Square);

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

   free(pGame);
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

   int nMaxColIndicators = MetricsGetMaxColIndicators(pGame->m_pMetrics);
   int nMaxRowIndicators = MetricsGetMaxRowIndicators(pGame->m_pMetrics);

   int nPieceDim = MetricsGetPieceDim(pGame->m_pMetrics);

   int nLeft = MetricsGetLeft(pGame->m_pMetrics);
   int nTop = MetricsGetTop(pGame->m_pMetrics);

   int nLeftBoard = MetricsGetLeftBoard(pGame->m_pMetrics);
   int nTopBoard = MetricsGetTopBoard(pGame->m_pMetrics);

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
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         PieceDraw(pPiece, &gc);
      }
   }

   //Draw selector
   SelectorDraw(pGame->m_pSelector, &gc);

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

