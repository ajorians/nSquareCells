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

struct Cell
{
   int m_bIsBomb;
   int m_bMarked;
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
   int m_nRemaining;
   int m_nMistakesMade;
   struct SquareBoard* m_pBoard;
};

int SquareLibCreate(SquareLib* api, const char* pstrFile)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = malloc(sizeof(struct SquareCells));
   if( pS == NULL ){//Out of memory
      return SQUARELIB_OUT_OF_MEMORY;
   }

   pS->m_pBoard = malloc(sizeof(struct SquareBoard));
   if( pS->m_pBoard == NULL ){//Out of memory
      free(pS);
      return SQUARELIB_OUT_OF_MEMORY;
   }

   pS->m_nMistakesMade = 0;

   if( strstr(pstrFile, "SquareCells ") != pstrFile ) {//SquareCells file version check
      free(pS->m_pBoard);
      pS->m_pBoard = NULL;
      free(pS);
      pS = NULL;
      return SQUARELIB_NOT_PUZZLE_FILE;
   }

   if( strstr(pstrFile, "1 ") != (pstrFile + strlen("SquareCells ")) ) {//Version check
      free(pS->m_pBoard);
      pS->m_pBoard = NULL;
      free(pS);
      pS = NULL;
      return SQUARELIB_NOT_PUZZLE_FILE;
   }

   char* pstr = pstrFile + strlen("SquareCells 1 ");
   char buffer[16];
   int nSpotInBuffer = 0;

   int nRemaining = -1, nWidth = -1, nHeight = -1;
   int nX = -1, nY = -1, nSpotValue = -1;
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

         if( nRemaining < 0 ) {
            nRemaining = nValue;
            pS->m_nRemaining = nRemaining;
         }
         else if( nWidth < 0 ) {
            nWidth = nValue;
            pS->m_pBoard->m_nWidth = nWidth;
         }
         else if( nHeight < 0 ) {
            int x, y;

            nHeight = nValue;
            pS->m_pBoard->m_nHeight = nHeight;

            pS->m_pBoard->m_pItems = malloc(nWidth*nHeight*sizeof(struct Cell));

            if( pS->m_pBoard->m_pItems == NULL ) {//Out of memory
               free(pS->m_pBoard);
               pS->m_pBoard = NULL;
               free(pS);
               pS = NULL;
               return SQUARELIB_OUT_OF_MEMORY;
            }

            pS->m_pBoard->m_pTop = malloc(nWidth*sizeof(enum IndicatorType));
            if( pS->m_pBoard->m_pTop == NULL ) {//Out of memory
               free(pS->m_pBoard->m_pItems);
               pS->m_pBoard->m_pItems = NULL;
               free(pS->m_pBoard);
               pS->m_pBoard = NULL;
               free(pS);
               pS = NULL;
               return SQUARELIB_OUT_OF_MEMORY;
            }

            pS->m_pBoard->m_pLeft = malloc(nWidth*sizeof(enum IndicatorType));
            if( pS->m_pBoard->m_pLeft == NULL ) {//Out of memory
               free(pS->m_pBoard->m_pTop);
               pS->m_pBoard->m_pTop = NULL;
               free(pS->m_pBoard->m_pItems);
               pS->m_pBoard->m_pItems = NULL;
               free(pS->m_pBoard);
               pS->m_pBoard = NULL;
               free(pS);
               pS = NULL;
               return SQUARELIB_OUT_OF_MEMORY;
            }

            for(x=0; x<nWidth; x++) {
               for(y=0; y<nHeight; y++) {
                  struct Cell* pCell = GetAt(pS->m_pBoard, x, y);
                  pCell->m_bIsBomb = 0;
                  pCell->m_bMarked = 0;
                  pCell->m_nValue = 0;
               }
            }
            for(x=0; x<nWidth; x++) {
               *(pS->m_pBoard->m_pTop + x) = 0;
            }
            for(y=0; y<nHeight; y++) {
               *(pS->m_pBoard->m_pLeft + y) = 0;
            }
         }
         else if( nIndicatorSpots < (nWidth+nHeight) ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 2 ) {
                  printf("Invalid IndicatorType value of %d\n", nValue);
               }
#endif

               if( nIndicatorSpots < nWidth ) {
                  *(pS->m_pBoard->m_pTop + nIndicatorSpots) = nValue;
               }
               else {
                  *(pS->m_pBoard->m_pLeft + (nWidth - nIndicatorSpots)) = nValue;
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
            else if( nSpotValue <= -1 ) {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 20 ) {
                  printf("Invalid spot value for spot %d,%d with value %d\n", nX, nY, nValue);
               }
#endif
               nSpotValue = nValue;
            }
            else {
#ifdef SQUARELIB_RUN_SAFE
               if( nValue < 0 || nValue > 1 ) {
                  printf("Invalid bomb marking for spot %d,%d with value %d\n", nX, nY, nValue);
               }
#endif

               struct Cell* pCell = GetAt(pS->m_pBoard, nX, nY);
               pCell->m_bIsBomb = nValue;
               pCell->m_nValue = nValue;

               nX = nY = nSpotValue = -1;
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
