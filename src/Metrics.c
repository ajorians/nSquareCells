#include "Metrics.h"
#include <os.h>
#include <libndls.h>
#include <ngc.h>

void CreateMetrics(struct Metrics** ppMetrics, SquareLib square, Gc* pgc)
{
   *ppMetrics = malloc(sizeof(struct Metrics));
   struct Metrics* pMetrics = *ppMetrics;
   pMetrics->m_Square = square;

   int nWidth = GetSquareWidth(square);
   int nHeight = GetSquareHeight(square);

   pMetrics->m_nMaxColIndicators = 0;
   for(int x=0; x<nWidth; x++) {
      int nIndicators = GetNumSquareIndicatorsForCol(square, x);
      if( nIndicators > pMetrics->m_nMaxColIndicators )
         pMetrics->m_nMaxColIndicators = nIndicators;
   }
   printf("Max col indicators: %d\n", pMetrics->m_nMaxColIndicators);

   pMetrics->m_nMaxRowIndicators = 0;
   for(int y=0; y<nHeight; y++) {
      int nIndicators = GetNumSquareIndicatorsForRow(square, y);
      if( nIndicators > pMetrics->m_nMaxRowIndicators )
         pMetrics->m_nMaxRowIndicators = nIndicators;
   }
   printf("Max row indicators: %d\n", pMetrics->m_nMaxRowIndicators);

   char buffer[16];
   char buf[8];
   sprintf(buf, "%d", 8/*Example wide character*/);
   ascii2utf16(buffer, buf, 16);

   gui_gc_setFont(*pgc, SerifRegular7);
   const int nHorizontalSpacing = 3;
   int nWidthPerChar = gui_gc_getStringWidth(*pgc, gui_gc_getFont(*pgc), buf, 0, 1) + nHorizontalSpacing;

   const int nGapHorizontally = 4;
   const int nGapVertically = 4;
   int nIndicatorSpaceNeededHorizontally = pMetrics->m_nMaxRowIndicators * nWidthPerChar;
   int nSpaceAvailableHorizontally = SCREEN_WIDTH - nGapHorizontally - nIndicatorSpaceNeededHorizontally;
   printf("Space available Horizontall: %d\n", nSpaceAvailableHorizontally);

   int nHeightPerChar = gui_gc_getStringSmallHeight(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
   printf("HeightPerChar: %d\n", nHeightPerChar);
   int nIndicatorSpaceNeededVertically = pMetrics->m_nMaxColIndicators * nHeightPerChar;
   printf("IndicatorSpaceNeededVertically: %d\n", nIndicatorSpaceNeededVertically);
   int nSpaceAvailableVertically = SCREEN_HEIGHT - nGapVertically - nIndicatorSpaceNeededVertically;
   printf("Space available vertically: %d\n", nSpaceAvailableVertically);

   int nMinSpaceAvailable = nSpaceAvailableHorizontally < nSpaceAvailableVertically ? nSpaceAvailableHorizontally - (nWidth-1) : nSpaceAvailableVertically - (nHeight-1);

   int nPieceWidth = nMinSpaceAvailable / nWidth;
   int nPieceHeight = nSpaceAvailableVertically / nHeight;
   pMetrics->m_nPieceDim = nPieceWidth < nPieceHeight ? nPieceWidth : nPieceHeight;
   printf("PieceDim: %d\n", pMetrics->m_nPieceDim);

   int nBoardDim = ((pMetrics->m_nPieceDim * nWidth) > (pMetrics->m_nPieceDim * nHeight)) ? pMetrics->m_nPieceDim * nWidth : pMetrics->m_nPieceDim * nHeight;

   pMetrics->m_nLeftBoard = SCREEN_WIDTH - nGapHorizontally - nBoardDim;
   pMetrics->m_nTopBoard = nIndicatorSpaceNeededVertically;

   pMetrics->m_nLeft = pMetrics->m_nLeftBoard - nIndicatorSpaceNeededHorizontally;
   pMetrics->m_nTop = 0;
}

void FreeMetrics(struct Metrics** ppMetrics)
{
   struct Metrics* pMetrics = *ppMetrics;
   pMetrics->m_Square = NULL;//Does not own
   free(*ppMetrics);
   *ppMetrics = NULL;
}

int MetricsGetPieceDim(struct Metrics* pMetrics)
{
//   printf("PieceDim: %d\n", pMetrics->m_nPieceDim);
   return pMetrics->m_nPieceDim;
}

int MetricsGetMaxColIndicators(struct Metrics* pMetrics)
{
   return pMetrics->m_nMaxColIndicators;
}

int MetricsGetMaxRowIndicators(struct Metrics* pMetrics)
{
   return pMetrics->m_nMaxRowIndicators;
}

int MetricsGetLeft(struct Metrics* pMetrics)
{
   //printf("Left: %d\n", pMetrics->m_nLeft);
   return pMetrics->m_nLeft;
}

int MetricsGetTop(struct Metrics* pMetrics)
{
   //printf("Top: %d\n", pMetrics->m_nTop);
   return pMetrics->m_nTop;
}

int MetricsGetLeftBoard(struct Metrics* pMetrics)
{
   //printf("LeftBoard: %d\n", pMetrics->m_nLeftBoard);
   return pMetrics->m_nLeftBoard;
}

int MetricsGetTopBoard(struct Metrics* pMetrics)
{
   //printf("TopBoard: %d\n", pMetrics->m_nTopBoard);
   return pMetrics->m_nTopBoard;
}

int MetricsGetXForSpot(struct Metrics* pMetrics, int nX, int nY)
{
   return pMetrics->m_nLeftBoard + nX * pMetrics->m_nPieceDim;
}

int MetricsGetYForSpot(struct Metrics* pMetrics, int nX, int nY)
{
   return pMetrics->m_nTopBoard + nY * pMetrics->m_nPieceDim;
}


