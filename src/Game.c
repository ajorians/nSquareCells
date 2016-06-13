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
   pGame->m_R = 242;
   pGame->m_G = 242;
   pGame->m_B = 242;

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

void DrawMistakes(int nMistakes, Gc* pgc)
{
   if( nMistakes <= 0 )
      return;

   gui_gc_setColorRGB(*pgc, 127, 127, 127);
   const int nSquareSize = 5;
   int nSquaresToDraw = nMistakes;
   if( nMistakes > 5 ) nSquaresToDraw = 5;

   int nX = 22, nY = 28;
   for(int i=0; i<nSquaresToDraw; i++) {
      gui_gc_fillRect(*pgc, nX, nY, nSquareSize, nSquareSize);
      nX += nSquareSize;
      nX += 2;
   }
}

void DrawBoard(struct Game* pGame)
{
   /*pGame->m_R++%255;
   pGame->m_G++%255;
   pGame->m_B++%255;*/
   gui_gc_setColorRGB(pGame->m_gc, pGame->m_R, pGame->m_G, pGame->m_B);
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

   gui_gc_drawLine(pGame->m_gc, 9, 23, 22, 23);

   sprintf(buffer, "%d", nWidth*nHeight);
   ascii2utf16(bufferUnicode, buffer, 32);
   gui_gc_drawString(pGame->m_gc, bufferUnicode, 10, 23, GC_SM_TOP);

   //Draw mistakes
   DrawMistakes(GetSquareMistakes(pGame->m_Square), &pGame->m_gc);

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
   int nDestroyed = 0, nMarked = 0;
   if( IsKeyPressed(KEY_NSPIRE_ESC) ) {
      pGame->m_bShouldQuit = 0;//Could change to completly close program
      return 0;
   }
   else if( IsKeyPressed(KEY_NSPIRE_LEFT) ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Left);
   }
   else if( IsKeyPressed(KEY_NSPIRE_RIGHT) ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Right);
   }
   else if( IsKeyPressed(KEY_NSPIRE_UP) ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Up);
   }
   else if( IsKeyPressed(KEY_NSPIRE_DOWN) ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Down);
   }
   else if( IsKeyPressed(KEY_NSPIRE_CTRL) ) {
      wait_no_key_pressed();

      IsSquareMarked(pGame->m_Square, nSelectionX, nSelectionY, &nMarked);
      if( nMarked == SQUARELIB_NOT_MARKED ) {

         IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
         if( nDestroyed == SQUARELIB_NOT_DESTROYED )
            DestroySquare(pGame->m_Square, nSelectionX, nSelectionY);

         //Check if destroyed because if not you made a mistake
         IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
         if( nDestroyed == SQUARELIB_NOT_DESTROYED ) {
            int nWidth = GetSquareWidth(pGame->m_Square);
            struct Piece* pPiece = &pGame->m_apPieces[nSelectionX+nSelectionY*nWidth];
            PieceMistaken(pPiece);
         }

      }
   }
   else if( IsKeyPressed(KEY_NSPIRE_SHIFT) ) {
      wait_no_key_pressed();
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

