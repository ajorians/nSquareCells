#include "Metrics.h"
#include <os.h>
#include <libndls.h>
#include <ngc.h>

void CreateMetrics(struct Metrics** ppMetrics, SquareLib square)
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

   pMetrics->m_nMaxRowIndicators = 0;
   for(int y=0; y<nHeight; y++) {
      int nIndicators = GetNumSquareIndicatorsForRow(square, y);
      if( nIndicators > pMetrics->m_nMaxRowIndicators )
         pMetrics->m_nMaxRowIndicators = nIndicators;
   }

   int nSpotsNeededHorizontally = nWidth + pMetrics->m_nMaxRowIndicators;
   int nSpotsNeededVertically = nHeight + pMetrics->m_nMaxColIndicators;

   int nPieceWidth = SCREEN_WIDTH / nSpotsNeededHorizontally;
   int nPieceHeight = SCREEN_HEIGHT / nSpotsNeededVertically;
   pMetrics->m_nPieceDim = nPieceWidth < nPieceHeight ? nPieceWidth : nPieceHeight;

   pMetrics->m_nLeft = (SCREEN_WIDTH - (pMetrics->m_nPieceDim * nSpotsNeededHorizontally))/2;
   pMetrics->m_nTop = (SCREEN_HEIGHT - (pMetrics->m_nPieceDim * nSpotsNeededVertically))/2;

   pMetrics->m_nLeftBoard = pMetrics->m_nLeft + pMetrics->m_nMaxColIndicators*pMetrics->m_nPieceDim;
   pMetrics->m_nTopBoard = pMetrics->m_nTop + pMetrics->m_nMaxRowIndicators*pMetrics->m_nPieceDim;
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
   //printf("TopBoard: %d\n", pMetrics->m_pTopBoard);
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


