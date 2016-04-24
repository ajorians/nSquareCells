//Public domain :)

#ifdef _TINSPIRE
#include <os.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif
#include "SquareLib/SquareLib.h"
#include "Defines.h"

#define SQUARELIB_RUN_SAFE

//#define DEBUG_DETAILS
enum Marking
{
   NotMarked = 0,
   Marked    = 1,
   Destroyed = 2
};

struct Cell
{
   int m_bIsBomb;
   enum Marking m_eMarked;
   int m_nValue;//0 otherwise
};

struct SquareBoard
{
   int m_nWidth;
   int m_nHeight;
   struct Cell* m_pItems;
   enum IndicatorType* m_pTop;
   enum IndicatorType* m_pLeft;
};

struct Cell* GetAt(struct SquareBoard* pBoard, int nX, int nY)
{
#ifdef SQUARELIB_RUN_SAFE
   if( nX < 0 || nY < 0 || (nX >= pBoard->m_nWidth) || (nY >= pBoard->m_nHeight)) {
      printf("Accessing non-existing element %d,%d\n", nX, nY);
      return NULL;
   }
#endif

   struct Cell* pItem = pBoard->m_pItems + (pBoard->m_nWidth * nY + nX);

   return pItem;
}

struct SquareCells
{
   int m_nLastError;
   int m_nMistakesMade;
   struct SquareBoard* m_pBoard;
};

void Cleanup(struct SquareCells** ppS)
{
   if( *ppS != NULL ) {
      struct SquareCells* pS = *ppS;
      if( pS->m_pBoard != NULL ) {
         if( pS->m_pBoard->m_pItems != NULL ) {
            free(pS->m_pBoard->m_pItems);
            pS->m_pBoard->m_pItems = NULL;
         }
         if( pS->m_pBoard->m_pTop != NULL ) {
            free(pS->m_pBoard->m_pTop);
            pS->m_pBoard->m_pTop = NULL;
         }
         if( pS->m_pBoard->m_pLeft != NULL ) {
            free(pS->m_pBoard->m_pLeft);
            pS->m_pBoard->m_pLeft = NULL;
         }
         free(pS->m_pBoard);
         pS->m_pBoard = NULL;
      }
   }
}

int SquareLibCreate(SquareLib* api, const char* pstrFile)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = malloc(sizeof(struct SquareCells));
   if( pS == NULL ){//Out of memory
      return SQUARELIB_OUT_OF_MEMORY;
   }
   pS->m_pBoard = NULL;

   pS->m_pBoard = malloc(sizeof(struct SquareBoard));
   if( pS->m_pBoard == NULL ){//Out of memory
      Cleanup(&pS);
      return SQUARELIB_OUT_OF_MEMORY;
   }

   pS->m_pBoard->m_pItems = NULL;
   pS->m_pBoard->m_pTop = NULL;
   pS->m_pBoard->m_pLeft = NULL;

   pS->m_nMistakesMade = 0;

   if( strstr(pstrFile, "SquareCells ") != pstrFile ) {//SquareCells file version check
      printf("Not SquareCells data\n");
      Cleanup(&pS);
      return SQUARELIB_NOT_PUZZLE_FILE;
   }

   if( strstr(pstrFile, "1 ") != (pstrFile + strlen("SquareCells ")) ) {//Version check
      printf("Unable to read SquareCells data\n");
      Cleanup(&pS);
      return SQUARELIB_NOT_PUZZLE_FILE;
   }

   char* pstr = pstrFile + strlen("SquareCells 1 ");

   char buffer[16];
   int nSpotInBuffer = 0;

   int nRemaining = -1, nWidth = -1, nHeight = -1;
   int nX = -1, nY = -1, nIsBomb = -1;
   int nIndicatorSpots = 0;
   while(pstr != '\0') {
      char ch = *pstr; pstr++;
      if( isdigit(ch) ) {
         buffer[nSpotInBuffer++] = ch;
      }
      else {
         if( !isspace(ch) )
            break;
         buffer[nSpotInBuffer] = '\0';
         nSpotInBuffer = 0;
         int nValue = atoi(buffer);

#ifdef DEBUG_DETAILS
         printf("Value %d\n", nValue);
#endif

         if( nWidth < 0 ) {
#ifdef SQUARELIB_RUN_SAFE
            if( nValue < 0 || nValue > 20 ) {
               printf("Bad value for width of value %d\n", nValue);
            }
#endif
            nWidth = nValue;
            pS->m_pBoard->m_nWidth = nWidth;
         }
         else if( nHeight < 0 ) {
            int x, y;

#ifdef SQUARELIB_RUN_SAFE
            if( nValue < 0 || nValue > 20 ) {
               printf("Bad value for height of value %d\n", nValue);
            }
#endif

            nHeight = nValue;
            pS->m_pBoard->m_nHeight = nHeight;

            pS->m_pBoard->m_pItems = malloc(nWidth*nHeight*sizeof(struct Cell));

            if( pS->m_pBoard->m_pItems == NULL ) {//Out of memory
               Cleanup(&pS);
               return SQUARELIB_OUT_OF_MEMORY;
            }

            pS->m_pBoard->m_pTop = malloc(nWidth*sizeof(enum IndicatorType));
            if( pS->m_pBoard->m_pTop == NULL ) {//Out of memory
               Cleanup(&pS);
               return SQUARELIB_OUT_OF_MEMORY;
            }

            pS->m_pBoard->m_pLeft = malloc(nHeight*sizeof(enum IndicatorType));
            if( pS->m_pBoard->m_pLeft == NULL ) {//Out of memory
               Cleanup(&pS);
               return SQUARELIB_OUT_OF_MEMORY;
            }

            for(x=0; x<nWidth; x++) {
               for(y=0; y<nHeight; y++) {
                  struct Cell* pCell = GetAt(pS->m_pBoard, x, y);
                  pCell->m_bIsBomb = 0;
                  pCell->m_eMarked = NotMarked;
                  pCell->m_nValue = 0;
               }
            }
            for(x=0; x<nWidth; x++) {
               *(pS->m_pBoard->m_pTop + x) = NoNumber;
            }
            for(y=0; y<nHeight; y++) {
               *(pS->m_pBoard->m_pLeft + y) = NoNumber;
            }
         }
         else if( nIndicatorSpots < (nWidth+nHeight) ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 2 ) {
                  printf("Invalid IndicatorType value of %d\n", nValue);
               }
#endif

#ifdef DEBUG_DETAILS
               printf("Indicator type: %d for indicator spot %d\n", nValue, nIndicatorSpots);
#endif
               if( nIndicatorSpots < nWidth ) {
                  *(pS->m_pBoard->m_pTop + nIndicatorSpots) = nValue;
               }
               else {
                  *(pS->m_pBoard->m_pLeft + (nIndicatorSpots - nWidth)) = nValue;
               }
               nIndicatorSpots++;
         }
         else {
            if( nX <= -1 ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue >= pS->m_pBoard->m_nWidth ) {
                  printf("Invalid x value set of %d\n", nValue);
               }
#endif
               nX = nValue;
            }
            else if( nY <= -1 ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue >= pS->m_pBoard->m_nHeight ) {
                  printf("Invalid y value set of %d\n", nValue);
               }
#endif

               nY = nValue;
            }
            else if( nIsBomb <= -1 ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 1 ) {
                  printf("Invalid bomb marking for spot %d,%d with value %d\n", nX, nY, nValue);
               }
#endif
               nIsBomb = nValue;
            }
            else {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 20 ) {
                  printf("Invalid spot value for spot %d,%d with value %d\n", nX, nY, nValue);
               }
#endif

#ifdef DEBUG_DETAILS
               printf("Settings spot %d,%d; bomb: %d, spotValue: %d\n", nX, nY, nIsBomb, nValue);
#endif
               struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
               pCell->m_bIsBomb = nIsBomb;
               pCell->m_nValue = nValue;

               nX = nY = nIsBomb = -1;
            }
         }
      }
   } 

   pS->m_nLastError = SQUARELIB_OK;
   *api = pS;

   return SQUARELIB_OK;
}

int SquareLibFree(SquareLib* api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = *api;

   if( pS->m_pBoard != NULL ) {
      free(pS->m_pBoard);
      pS->m_pBoard = NULL;
   }

   free(pS);
   *api = NULL;
   return SQUARELIB_OK;
}

int GetSquareLibError(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   return pS->m_nLastError;
}

void ClearSquareLibError(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   pS->m_nLastError = SQUARELIB_OK;
}

//SquareLib related functions
int GetSquareWidth(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   return pS->m_pBoard->m_nWidth;
}

int GetSquareHeight(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   return pS->m_pBoard->m_nHeight;
}

int ToggleSquareMark(SquareLib api, int nX, int nY)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nX < 0 || nX >= pS->m_pBoard->m_nWidth || nY < 0 || nY >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
   if( pCell->m_eMarked == Destroyed )
      return SQUARELIB_BADARGUMENT;

#ifdef DEBUG_DETAILS
   printf("Whether cell at %d,%d was previously unmarked: %d\n", nX, nY, pCell->m_eMarked == NotMarked);
#endif
   pCell->m_eMarked = pCell->m_eMarked == NotMarked ? Marked : NotMarked;
   return SQUARELIB_OK;
}

int IsSquareMarked(SquareLib api, int nX, int nY, int* pMarked)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nX < 0 || nX >= pS->m_pBoard->m_nWidth || nY < 0 || nY >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
   if( pMarked ) {
      *pMarked = pCell->m_eMarked == Marked ? SQUARELIB_MARKED : SQUARELIB_NOT_MARKED;
   }
   return SQUARELIB_OK;
}

int DestroySquare(SquareLib api, int nX, int nY)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nX < 0 || nX >= pS->m_pBoard->m_nWidth || nY < 0 || nY >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
   if( pCell->m_bIsBomb ) {
      printf("Attempted to destroy cell that is a bomb: %d,%d\n", nX, nY);
      //TODO: Increase mistake count
      pCell->m_eMarked = Marked;
   }
   else {
      pCell->m_eMarked = Destroyed;
   }
   return SQUARELIB_OK;
}

int IsSquareDestroyed(SquareLib api, int nX, int nY, int* pDestroyed)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nX < 0 || nX >= pS->m_pBoard->m_nWidth || nY < 0 || nY >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
   if( pDestroyed ) {
      *pDestroyed = pCell->m_eMarked == Destroyed ? SQUARELIB_DESTROYED : SQUARELIB_NOT_DESTROYED;
   }
   return SQUARELIB_OK;
}

int GetSquaresRemaining(SquareLib api)
{
   struct SquareCells* pS;
   int x,y;
   int nCount = 0;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   for(x=0; x<pS->m_pBoard->m_nWidth; x++) {
      for(y=0; y<pS->m_pBoard->m_nHeight; y++) {
         struct Cell* pCell = GetAt(pS->m_pBoard, x, y);
#ifdef DEBUG_DETAILS
         printf("Spot %d,%d is marked: %d, is bomb: %d\n", x, y, pCell->m_eMarked == Marked, pCell->m_bIsBomb == 1);
#endif
         if( pCell->m_eMarked != Destroyed && pCell->m_bIsBomb == 0 )
            nCount++;
      }
   }
#ifdef DEBUG_DETAILS
   printf("Count: %d\n", nCount);
#endif
   return nCount;
}

int IsSquareGameOver(SquareLib api)
{
   struct SquareCells* pS;
   int x,y;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   for(x=0; x<pS->m_pBoard->m_nWidth; x++) {
      for(y=0; y<pS->m_pBoard->m_nHeight; y++) {
         struct Cell* pCell = GetAt(pS->m_pBoard, x, y);
         if( pCell->m_eMarked == NotMarked ) {
#ifdef DEBUG_DETAILS
            printf("Unmarked spot %d,%d\n", x, y);
#endif
            return SQUARELIB_NOT_GAMEOVER;
         }
         else if( pCell->m_eMarked == Marked ) {
            //Check to see if a bomb
            if( pCell->m_bIsBomb == 0 ) {
#ifdef DEBUG_DETAILS
               printf("Marked spot that isn't a bomb: %d,%d\n", x, y);
#endif
               return SQUARELIB_NOT_GAMEOVER;
            }

            if( pCell->m_nValue != 0 ) {
               if( SQUARELIB_NUMBER_VAL_MET != IsSquareNumberMet(api, x, y) ) {
#ifdef DEBUG_DETAILS
                  printf("Value not satisfied at %d,%d\n", x, y);
#endif
                  return SQUARELIB_NOT_GAMEOVER;
               }
            }
         }
      }
   }
   if( 0 != GetSquaresRemaining(api) ) {
#ifdef DEBUG_DETAILS
      printf("Squares remaining != 0\n");
#endif
      return SQUARELIB_NOT_GAMEOVER;
   }

   return SQUARELIB_GAMEOVER;
}

int IsSquareNumberMet(SquareLib api, int nX, int nY)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nX < 0 || nX >= pS->m_pBoard->m_nWidth || nY < 0 || nY >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
   if( pCell->m_nValue <=0 )
      return SQUARELIB_BADARGUMENT;

   //TODO: Needs to verify.  For now returning true
   return SQUARELIB_NUMBER_VAL_MET;
}
/*
int NumberOfBombsInCol(struct SquareCells* pS, int nIndex)
{
   int nCount = 0;
   int y;
   DEBUG_FUNC_NAME;
   if( nIndex < 0 || nIndex > pS->m_pBoard->m_nWidth )
      return -1;

   for(y=0; y<pS->m_pBoard->m_nHeight; y++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, nIndex, y);
      if( pCell->m_bIsBomb )
         nCount++;
   }

   return nCount;
}

int NumberOfBombsInRow(struct SquareCells* pS, int nIndex)
{
   int nCount = 0;
   int x;
   DEBUG_FUNC_NAME;
   if( nIndex < 0 || nIndex > pS->m_pBoard->m_nHeight )
      return -1;

   for(x=0; x<pS->m_pBoard->m_nWidth; x++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, x, nIndex);
      if( pCell->m_bIsBomb )
         nCount++;
   }

   return nCount;
}*/

int GetNumSquareIndicatorsForRow(SquareLib api, int nIndex)
{
   struct SquareCells* pS;
   enum IndicatorType eType;
   int nCount = 0;
   int i = 0;
   int x;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nHeight )
      return -1;

   eType = *(pS->m_pBoard->m_pLeft + nIndex);
   if( eType == NoNumber ) {
      return 0;
   }

   for(x=0; x<pS->m_pBoard->m_nWidth; x++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, x, nIndex);
      if( pCell->m_bIsBomb )
         nCount++;

      if( !pCell->m_bIsBomb && eType == Sequential && nCount > 0 ) {
         i++;
         nCount = 0;
      }
   }

   if( nCount > 0 )
      i++;

   return i;
}
int GetNumSquareIndicatorsForCol(SquareLib api, int nIndex)
{
   struct SquareCells* pS;
   enum IndicatorType eType;
   int nCount = 0;
   int i = 0;
   int y;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nWidth )
      return -1;

   eType = *(pS->m_pBoard->m_pTop + nIndex);
   if( eType == NoNumber ) {
      return 0;
   }

   for(y=0; y<pS->m_pBoard->m_nHeight; y++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, nIndex, y);
      if( pCell->m_bIsBomb )
         nCount++;

      if( !pCell->m_bIsBomb && eType == Sequential && nCount > 0 ) {
         i++;
         nCount = 0;
      }
   }

   if( nCount > 0 )
      i++;
   return i;
}

int GetSquareIndicatorsForRow(SquareLib api, int nIndex, int arr[8])
{
   struct SquareCells* pS;
   enum IndicatorType eType;
   int nCount = 0;
   int i = 0;
   int x;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nHeight )
      return -1;

   eType = *(pS->m_pBoard->m_pLeft + nIndex);
   if( eType == NoNumber ) {
#ifdef DEBUG_DETAILS
      printf("Row %d is a no number\n", nIndex);
#endif
      return 0;
   }

   for(x=0; x<pS->m_pBoard->m_nWidth; x++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, x, nIndex);
      if( pCell->m_bIsBomb )
         nCount++;

      if( !pCell->m_bIsBomb && eType == Sequential && nCount > 0 ) {
         arr[i++] = nCount;
         nCount = 0;
      }
   }
   if( nCount > 0 || i == 0 )
      arr[i++] = nCount;
#ifdef DEBUG_DETAILS
   printf("Row %d returning %d\n", nIndex, i);
#endif
   return i;
}

int GetSquareIndicatorsForCol(SquareLib api, int nIndex, int arr[8])
{
   struct SquareCells* pS;
   enum IndicatorType eType;
   int nCount = 0;
   int i = 0;
   int y;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nWidth )
      return -1;

   eType = *(pS->m_pBoard->m_pTop + nIndex);
   if( eType == NoNumber ) {
#ifdef DEBUG_DETAILS
      printf("Col %d is a no number\n", nIndex);
#endif
      return 0;
   }

   for(y=0; y<pS->m_pBoard->m_nHeight; y++) {
      struct Cell* pCell = GetAt(pS->m_pBoard, nIndex, y);
      if( pCell->m_bIsBomb )
         nCount++;

      if( !pCell->m_bIsBomb && eType == Sequential && nCount > 0 ) {
         arr[i++] = nCount;
         nCount = 0;
      }
   }
   if( nCount > 0 || i == 0 )
      arr[i++] = nCount;
#ifdef DEBUG_DETAILS
   printf("Col %d returning %d\n", nIndex, i);
#endif
   return i;
}

int GetSquareIndicatorTypeRow(SquareLib api, int nIndex, enum IndicatorType* pIndicator)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nHeight )
      return SQUARELIB_BADARGUMENT;

   if( pIndicator != NULL )
      *pIndicator = *(pS->m_pBoard->m_pLeft + nIndex);

   return SQUARELIB_OK;
}

int GetSquareIndicatorTypeCol(SquareLib api, int nIndex, enum IndicatorType* pIndicator)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   if( nIndex < 0 || nIndex >= pS->m_pBoard->m_nWidth )
      return SQUARELIB_BADARGUMENT;

   if( pIndicator != NULL )
      *pIndicator = *(pS->m_pBoard->m_pTop + nIndex);

   return SQUARELIB_OK;
}












