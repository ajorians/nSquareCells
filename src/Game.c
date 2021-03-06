#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Game.h"
#include "Metrics.h"
#include "Piece.h"
#include "Selector.h"
#include "Indicators.h"

void DrawWin(struct Game* pGame);
int GetStarCount(struct Game* pGame);

void CreateGame(struct Game** ppGame, const char* pstrLevelData, int nLevelNum, struct Config* pConfig)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   SquareLibCreate(&(pGame->m_Square), pstrLevelData);
   pGame->m_nLevelNum = nLevelNum;
   pGame->m_pConfig = pConfig;
   pGame->m_bWon = IsSquareGameOver(pGame->m_Square);

   pGame->m_gc = gui_gc_global_GC();

   gui_gc_begin(pGame->m_gc);
   pGame->m_pMetrics = NULL;
   CreateMetrics(&pGame->m_pMetrics, pGame->m_Square, &pGame->m_gc);

   int nWidth = GetSquareWidth(pGame->m_Square);
   int nHeight = GetSquareHeight(pGame->m_Square);
   int nNumPtrs = nWidth * nHeight;
   int nColorIndex = 0;
   if( nLevelNum >= 7 && nLevelNum < 13 ) {
      nColorIndex = 1;
   } else if( nLevelNum >= 13 && nLevelNum < 19 ) {
      nColorIndex = 2;
   } else if( nLevelNum >= 19 && nLevelNum < 25 ) {
      nColorIndex = 3;
   } else if( nLevelNum >= 25 && nLevelNum < 31 ) {
      nColorIndex = 4;
   } else if( nLevelNum >= 31 ) {
      nColorIndex = 5;
   }
   pGame->m_apPieces = malloc(nNumPtrs*sizeof(struct Piece));
   for(int x=0; x<nWidth; x++) {
      for(int y=0; y<nHeight; y++) {
         struct Piece* pPiece = &pGame->m_apPieces[x+y*nWidth];
         CreatePiece(pPiece, x, y, pGame->m_Square, pGame->m_pMetrics, nColorIndex);
      }
   }

   pGame->m_pSelector = NULL;
   CreateSelector(&pGame->m_pSelector, pGame->m_Square, pGame->m_pMetrics);

   pGame->m_pIndicators = NULL;
   CreateIndicators(&pGame->m_pIndicators, pGame->m_Square, pGame->m_pMetrics);

   pGame->m_pBackground = NULL;
   CreateBackground(&pGame->m_pBackground, pConfig);

   pGame->m_pStarDrawer = NULL;
   CreateStarDrawer(&pGame->m_pStarDrawer);

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
   FreeStarDrawer(&pGame->m_pStarDrawer);

   pGame->m_pConfig = NULL;//Does not own

   gui_gc_finish(pGame->m_gc);

   free(pGame);
   *ppGame = NULL;
}

void DrawMistakes(int nMistakes, Gc* pgc, int nX)
{
   if( nMistakes <= 0 )
      return;

   gui_gc_setColorRGB(*pgc, 127, 127, 127);
   const int nSquareSize = 5;
   int nSquaresToDraw = nMistakes;
   if( nMistakes > 5 ) nSquaresToDraw = 5;

   int nY = 28;
   for(int i=0; i<nSquaresToDraw; i++) {
      gui_gc_fillRect(*pgc, nX, nY, nSquareSize, nSquareSize);
      nX += nSquareSize;
      nX += 2;
   }
}

void DrawMessage(struct Game* pGame)
{
   char message[256] = {0};
   strcpy(message, GetSquareMessage(pGame->m_Square));
   int nLength = strlen(message);

   int nLeft = MetricsGetLeft(pGame->m_pMetrics);

   int nStart = 0;
   int nLine = 0;

   const int nLeftIndent = 3;
   const int nSpaceAvailable = nLeft - nLeftIndent - 3/*little extra*/;
   while(1) {
      const int maxLine = 32;
      char buff[32] = {0};
      char buffer[64];

      //If starts with space skip it :)
      while( *(message + nStart) == ' ' )
         nStart++;
   
      int nRemainingCharacters = nLength - nStart;
      int nCharactersDraw = nRemainingCharacters > maxLine ? maxLine : nRemainingCharacters;
      if( nCharactersDraw <= 0 )
         break;

      int i=1;
      int nChars = 1;
      for(; i<=nCharactersDraw; i++) {
         nChars = i;
         memcpy( buff, message + nStart, i);

         ascii2utf16(buffer, buff, 2*maxLine);

         //Make new lines
         if( buff[i-1] == '\r' || buff[i-1] == '\n' ) {
            buffer[2*(i-1)] = '\0';
            break;
         }

         int nWidthSpaceDesired = gui_gc_getStringWidth(pGame->m_gc, gui_gc_getFont(pGame->m_gc), buffer, 0, i);
         if( nWidthSpaceDesired >= nSpaceAvailable )
            break;

         //If space and close to end break now
         if( buff[i-1]==' ' && (nWidthSpaceDesired + 25)>nSpaceAvailable ) {
            buffer[2*(i-1)] = '\0';
            break;
         }
      }

      //gui_gc_setColorRGB(pGame->m_gc, 0, 0, 0);
      gui_gc_drawString(pGame->m_gc, buffer, nLeftIndent, 40 + nLine * 11, GC_SM_TOP);
      nLine++;
      nStart += nChars;
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

   int nLength = strlen(buffer);
   int nWidthSpaceDesired = gui_gc_getStringWidth(pGame->m_gc, gui_gc_getFont(pGame->m_gc), bufferUnicode, 0, nLength);
   int nLeft = 10 + nWidthSpaceDesired;

   //Draw mistakes
   DrawMistakes(GetSquareMistakes(pGame->m_Square), &pGame->m_gc, nLeft);

   //Draw message
   DrawMessage(pGame);

   if( pGame->m_bWon == SQUARELIB_GAMEOVER ) {
      DrawWin(pGame);
   }

   gui_gc_blit_to_screen(pGame->m_gc);
}

int GetStarCount(struct Game* pGame)
{
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
   return nStars;
}

void DrawWin(struct Game* pGame)
{
   char buffer[32];
   strcpy(buffer, "You Win!!!");
   char bufferUnicode[32];
   ascii2utf16(bufferUnicode, buffer, 32);

   gui_gc_setFont(pGame->m_gc, Regular12);
   int nWidth = gui_gc_getStringWidth(pGame->m_gc, Regular12, bufferUnicode, 0, 10/*strlen("You Win!!!")*/);
   int nHeight = gui_gc_getStringHeight(pGame->m_gc, Regular12, bufferUnicode, 0, 10);

   gui_gc_setColorRGB(pGame->m_gc, 255, 0, 0);
   int x = (SCREEN_WIDTH - nWidth)/2;
   int y = (SCREEN_HEIGHT - nHeight)/2;
   gui_gc_drawString(pGame->m_gc, bufferUnicode, x, y, GC_SM_TOP);

   int nStars = GetStarCount(pGame);
   DrawStars(pGame->m_pStarDrawer, &pGame->m_gc, nStars, y+nHeight);
}

int IsKeyPressed(const t_key key){
   if( !isKeyPressed(key) )
      return 0;

   while( isKeyPressed(key) ){}

   return 1;
}

void UpdateGameWon(struct Game* pGame)
{
   if( pGame->m_bWon && pGame->m_nLevelNum > 0 && pGame->m_nLevelNum <= 36 ) {
      int nStars = GetStarCount(pGame);
      SetBeatLevel(pGame->m_pConfig, pGame->m_nLevelNum-1/*To 0-base*/, nStars);
   }
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
   else if( ( IsKeyPressed(KEY_NSPIRE_LEFT) || IsKeyPressed(KEY_NSPIRE_4) ) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Left);
   }
   else if( ( IsKeyPressed(KEY_NSPIRE_RIGHT) || IsKeyPressed(KEY_NSPIRE_6) ) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Right);
   }
   else if( ( IsKeyPressed(KEY_NSPIRE_UP) || IsKeyPressed(KEY_NSPIRE_8) ) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      SelectorMove(pGame->m_pSelector, Sel_Up);
   }
   else if( ( IsKeyPressed(KEY_NSPIRE_DOWN) || IsKeyPressed(KEY_NSPIRE_2) ) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
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
            if( pGame->m_bWon )
               UpdateGameWon( pGame );
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
   else if( ( IsKeyPressed(KEY_NSPIRE_SHIFT) || IsKeyPressed(KEY_NSPIRE_ENTER) ) && pGame->m_bWon != SQUARELIB_GAMEOVER ) {
      wait_no_key_pressed();
      IsSquareDestroyed(pGame->m_Square, nSelectionX, nSelectionY, &nDestroyed);
      if( nDestroyed == SQUARELIB_NOT_DESTROYED ) {
         ToggleSquareMark(pGame->m_Square, nSelectionX, nSelectionY);
         pGame->m_bWon = IsSquareGameOver(pGame->m_Square);
         if( pGame->m_bWon ) {
            UpdateGameWon( pGame );
         }
      }
   }

   return 1;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

