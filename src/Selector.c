#include "Selector.h"
#include <os.h>
#include <libndls.h>
#include "Metrics.h"

void CreateSelector(struct Selector** ppSelector, SquareLib square, struct Metrics* pMetrics)
{
   *ppSelector = malloc(sizeof(struct Selector));
   struct Selector* pSelector = *ppSelector;
   pSelector->m_Square = square;
   pSelector->m_pMetrics = pMetrics;
   pSelector->m_nSelectionX = pSelector->m_nSelectionY = 0;

}

void FreeSelector(struct Selector** ppSelector)
{
   struct Selector* pSelector = *ppSelector;
   pSelector->m_Square = NULL;//Does not own
   free(*ppSelector);
   *ppSelector = NULL;
}

void SelectorDraw(struct Selector* pSelector, Gc* pgc)
{
   int nPieceDim = MetricsGetPieceDim(pSelector->m_pMetrics);

   gui_gc_setColorRGB(*pgc, 255, 0, 0);
   int nSelectionX = MetricsGetXForSpot(pSelector->m_pMetrics, pSelector->m_nSelectionX, pSelector->m_nSelectionY),
       nSelectionY = MetricsGetYForSpot(pSelector->m_pMetrics, pSelector->m_nSelectionX, pSelector->m_nSelectionY);
   gui_gc_drawLine(*pgc, nSelectionX, nSelectionY, nSelectionX + nPieceDim, nSelectionY);
   gui_gc_drawLine(*pgc, nSelectionX, nSelectionY, nSelectionX, nSelectionY + nPieceDim);
   gui_gc_drawLine(*pgc, nSelectionX + nPieceDim, nSelectionY, nSelectionX + nPieceDim, nSelectionY + nPieceDim);
   gui_gc_drawLine(*pgc, nSelectionX, nSelectionY + nPieceDim, nSelectionX + nPieceDim, nSelectionY + nPieceDim);
}

void SelectorMove(struct Selector* pSelector, enum SelDirection eDirection)
{
   if( eDirection == Sel_Left && pSelector->m_nSelectionX > 0 )
      pSelector->m_nSelectionX--;
   else if( eDirection == Sel_Right && pSelector->m_nSelectionX < (GetSquareWidth(pSelector->m_Square)-1) )
      pSelector->m_nSelectionX++;
   else if( eDirection == Sel_Up && pSelector->m_nSelectionY > 0 )
      pSelector->m_nSelectionY--;
   else if( eDirection == Sel_Down && pSelector->m_nSelectionY < (GetSquareHeight(pSelector->m_Square)-1) )
      pSelector->m_nSelectionY++;

}





