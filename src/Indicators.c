#include "Indicators.h"
#include <os.h>
#include <libndls.h>
#include "Metrics.h"

void CreateIndicators(struct Indicators** ppIndicators, SquareLib square, struct Metrics* pMetrics)
{
   *ppIndicators = malloc(sizeof(struct Indicators));
   struct Indicators* pIndicators = *ppIndicators;
   pIndicators->m_Square = square;
   pIndicators->m_pMetrics = pMetrics;
}

void FreeIndicators(struct Indicators** ppIndicators)
{
   struct Indicators* pIndicators = *ppIndicators;
   pIndicators->m_Square = NULL;//Does not own
   free(*ppIndicators);
   *ppIndicators = NULL;
}

void IndicatorsDraw(struct Indicators* pIndicators, Gc* pgc)
{
   int nWidth = GetSquareWidth(pIndicators->m_Square);
   int nHeight = GetSquareHeight(pIndicators->m_Square);

   int nMaxColIndicators = MetricsGetMaxColIndicators(pIndicators->m_pMetrics);
   int nMaxRowIndicators = MetricsGetMaxRowIndicators(pIndicators->m_pMetrics);

   int nPieceDim = MetricsGetPieceDim(pIndicators->m_pMetrics);

   int nLeft = MetricsGetLeft(pIndicators->m_pMetrics);
   int nTop = MetricsGetTop(pIndicators->m_pMetrics);

   int nLeftBoard = MetricsGetLeftBoard(pIndicators->m_pMetrics);
   int nTopBoard = MetricsGetTopBoard(pIndicators->m_pMetrics);

   gui_gc_setFont(*pgc, SerifRegular7);
   gui_gc_setColorRGB(*pgc, 0, 0, 0);
   //Top indicators
   for(int x=0; x<nWidth; x++) {
      int arr[8] = {0};
      int nIndicators = GetSquareIndicatorsForCol(pIndicators->m_Square, x, arr);
      int nIndicatorOffset = nMaxColIndicators - nIndicators;
      enum IndicatorType eType;
      GetSquareIndicatorTypeCol(pIndicators->m_Square, x, &eType);
      for(int i=0; i<nIndicators; i++) {
         char buf[8];
         if( eType == FullNumbers )
            sprintf(buf, "[%d]", arr[i]);
         else
            sprintf(buf, "%d", arr[i]);
         char buffer[16];
         ascii2utf16(buffer, buf, 16);
         int nWidthSpaceDesired = gui_gc_getStringWidth(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
         int nHeightSpaceDesired = gui_gc_getStringSmallHeight(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
         static int n = 0;
         if( n == 0 )
         {
            printf("nHeightSpaceDesired: %d\n", nHeightSpaceDesired);
            n++;
         }
         int nPosX = nLeftBoard + x*nPieceDim + (nPieceDim-nWidthSpaceDesired)/2;
         int nPosY = nTop + (i+nIndicatorOffset)*nHeightSpaceDesired;
         gui_gc_drawString(*pgc, buffer, nPosX, nPosY, GC_SM_TOP);
      }
   }

   //Left side indicators
   for(int y=0; y<nHeight; y++) {
      int arr[8] = {0};
      int nIndicators = GetSquareIndicatorsForRow(pIndicators->m_Square, y, arr);
      int nIndicatorOffset = nMaxRowIndicators - nIndicators;
      enum IndicatorType eType;
      GetSquareIndicatorTypeRow(pIndicators->m_Square, y, &eType);
      for(int i=0; i<nIndicators; i++) {
         char buf[8];
         if( eType == FullNumbers )
            sprintf(buf, "[%d]", arr[i]);
         else
            sprintf(buf, "%d", arr[i]);
         char buffer[16];
         ascii2utf16(buffer, buf, 16);
         int nHeightSpaceDesired = gui_gc_getStringSmallHeight(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
         const int nHorizontalSpacing = 3;
         int nWidthSpaceDesired = gui_gc_getStringWidth(*pgc, gui_gc_getFont(*pgc), buf, 0, 1) + nHorizontalSpacing;
         int nPosX = nLeft + (i+nIndicatorOffset)*nWidthSpaceDesired;
         int nPosY = nTopBoard + y*nPieceDim + (nPieceDim-nHeightSpaceDesired)/2;
         gui_gc_drawString(*pgc, buffer, nPosX, nPosY, GC_SM_TOP);
      }
   }
}






