#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"
#include "Metrics.h"
#include "Piece.h"
#include "Selector.h"
#include "Indicators.h"

void DrawWin(struct Game* pGame);
void DrawStar(Gc* pgc, int x, int y, int a);

void CreateGame(struct Game** ppGame, const char* pstrLevelData)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   SquareLibCreate(&(pGame->m_Square), pstrLevelData);
   pGame->m_bWon = IsSquareGameOver(pGame->m_Square);

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

   pGame->m_pBackground = NULL;
   CreateBackground(&pGame->m_pBackground);

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
   FreeBackground(&pGame->m_pBackground);

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
   DrawBackground(pGame->m_pBackground, &pGame->m_gc);

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

   if( pGame->m_bWon == SQUARELIB_GAMEOVER ) {
      DrawWin(pGame);
   }

   gui_gc_blit_to_screen(pGame->m_gc);
}

typedef struct {
   unsigned int x;
   unsigned int y;
} point2D;
void DrawStar(Gc* pgc, int x, int y, int a)
{
   point2D points[] = {{a/2.0+x, -0.16246*a+y},
                   {0.190983*a+x, 0.0620541*a+y},
                   {0.309017*a+x, 0.425325*a+y},
                   {0+x, 0.200811*a+y},
                   {-0.309017*a+x, 0.425325*a+y},
                   {-0.190983*a+x, 0.0620541*a+y},
                   {-a/2.0+x, -0.16246*a+y},
                   {-0.118034*a+x, -0.16246*a+y},
                   {0+x, -0.525731*a+y},
                   {0.118034*a+x, -0.16246*a+y},
                   {a/2.0+x, -0.16246*a+y}};

   gui_gc_setColorRGB(*pgc, 255,215,0);
   gui_gc_fillPoly(*pgc, (unsigned*)points, sizeof (points) / sizeof (points[0]));
}

void DrawWin(struct Game* pGame)
{
   char buffer[32];
   strcpy(buffer, "You Win!!!");
   char bufferUnicode[32];
   ascii2utf16(bufferUnicode, buffer, 32);

   gui_gc_setFont(pGame->m_gc, Regular12);
   int nWidth = gui_gc_getStringWidth(pGame->m_gc, Regular12, buffer, 0, 10/*strlen("You Win!!!")*/);
   int nHeight = gui_gc_getStringHeight(pGame->m_gc, Regular12, buffer, 0, 10);

   gui_gc_setColorRGB(pGame->m_gc, 255, 0, 0);
   int x = (SCREEN_WIDTH - nWidth)/2;
   int y = (SCREEN_HEIGHT - nHeight)/2;
   gui_gc_drawString(pGame->m_gc, bufferUnicode, x, y, GC_SM_TOP);

   int nStars;
   int nMistakes = GetSquareMistakes(pGame->m_Square);
   if( nMistakes == 0 ) {
      nStars = 3;
   } else if( nMistakes >= 1 && nMistakes <= 2 ) {
      nStars = 2;
   }
   else {
      nStars = 1;
   }
   int a = 55;
   int nGapX = 5;
   int nStarX = (SCREEN_WIDTH-((nStars-1)*(a+nGapX)))/2;
   for(int i=0; i<nStars; i++) {
      DrawStar(&pGame->m_gc, nStarX + (nGapX+a)*i, y+nHeight+(a/2), a);
   }
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
   else if( IsKeyPressed(KEY_NSPIRE_LEFT) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Left);
   }
   else if( IsKeyPressed(KEY_NSPIRE_RIGHT) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Right);
   }
   else if( IsKeyPressed(KEY_NSPIRE_UP) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Up);
   }
   else if( IsKeyPressed(KEY_NSPIRE_DOWN) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Down);
   }
   else if( IsKeyPressed(KEY_NSPIRE_CTRL) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();

      IsSquareMarked(pGame->m_Square, nSelectionX, nSelectionY, &nMarked);
      if( nMarked == SQUARELIB_NOT_MARKED ) {

         IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
         if( nDestroyed == SQUARELIB_NOT_DESTROYED ) {
            DestroySquare(pGame->m_Square, nSelectionX, nSelectionY);

            pGame->m_bWon = IsSquareGameOver(pGame->m_Square);
         }

         //Check if destroyed because if not you made a mistake
         IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
         if( nDestroyed == SQUARELIB_NOT_DESTROYED ) {
            int nWidth = GetSquareWidth(pGame->m_Square);
            struct Piece* pPiece = &pGame->m_apPieces[nSelectionX+nSelectionY*nWidth];
            PieceMistaken(pPiece);
         }

      }
   }
   else if( IsKeyPressed(KEY_NSPIRE_SHIFT) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED ) {
         ToggleSquareMark(pGame->m_Square, nSelectionX, nSelectionY);
         pGame->m_bWon = IsSquareGameOver(pGame->m_Square);
      }
   }

   return 1;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

