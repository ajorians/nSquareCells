#include "Piece.h"
#include <os.h>
#include <libndls.h>
#include "Metrics.h"

void CreatePiece(struct Piece* pPiece, int x, int y, SquareLib pSquare, struct Metrics* pMetrics)
{
   pPiece->m_nX = x;
   pPiece->m_nY = y;
   pPiece->m_pMetrics = pMetrics;
   pPiece->m_Square = pSquare;
}

void FreePiece(struct Piece* pPiece)
{
}

void PieceDraw(struct Piece* pPiece, Gc* pgc)
{
   int nPieceX = MetricsGetXForSpot(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY),
       nPieceY = MetricsGetYForSpot(pPiece->m_pMetrics, pPiece->m_nX, pPiece->m_nY);

   int nPieceDim = MetricsGetPieceDim(pPiece->m_pMetrics);

   int nDestroyed = 0, nMarked = 0;
   IsSquareDestroyed(pPiece->m_Square, pPiece->m_nX, pPiece->m_nY, &nDestroyed);
   if( nDestroyed == SQUARELIB_DESTROYED ) {
      int nSqSize = nPieceDim / 2;
      gui_gc_setColorRGB(*pgc, 127, 127, 127);
      gui_gc_fillRect(*pgc, nPieceX + nSqSize/2, nPieceY + nSqSize/2, nSqSize, nSqSize);
      return;
   }

   gui_gc_setColorRGB(*pgc, 255, 255, 255);
   gui_gc_drawRect(*pgc, nPieceX + 1, nPieceY + 1, nPieceDim-2, nPieceDim-2);

   gui_gc_setColorRGB(*pgc, 0, 220, 0);
   gui_gc_fillRect(*pgc, nPieceX + 2, nPieceY + 2, nPieceDim-3, nPieceDim-3);

   IsSquareMarked(pPiece->m_Square, pPiece->m_nX, pPiece->m_nY, &nMarked);
   if( nMarked == SQUARELIB_MARKED ) {
      gui_gc_setColorRGB(*pgc, 0, 175, 0);
      gui_gc_fillRect(*pgc, nPieceX + 2, nPieceY + nPieceDim/2 + 2, nPieceDim-3, nPieceDim/2-3);

      gui_gc_setColorRGB(*pgc, 255, 255, 255);
      gui_gc_fillRect(*pgc, nPieceX + nPieceDim - 12, nPieceY + 4, 6, 6);
   }

   int nSpotValue = 0;
   if( SQUARELIB_HAS_VALUE == GetSpotNumber(pPiece->m_Square, pPiece->m_nX, pPiece->m_nY, &nSpotValue) ) {
      gui_gc_setColorRGB(*pgc, 255, 255, 255);
      char buf[8];
      sprintf(buf, "%d", nSpotValue);
      char buffer[16];
      ascii2utf16(buffer, buf, 16);

      int nHeightSpaceDesired = gui_gc_getStringSmallHeight(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);
      int nWidthSpaceDesired = gui_gc_getStringWidth(*pgc, gui_gc_getFont(*pgc), buf, 0, 1);

      int nXOffset = nPieceDim/2 - nWidthSpaceDesired/2;
      int nYOffset = nPieceDim/2 - nHeightSpaceDesired/2;

      int nPosX = nPieceX + nXOffset;
      int nPosY = nPieceY + nYOffset;

      gui_gc_drawString(*pgc, buffer, nPosX, nPosY, GC_SM_TOP);
   }
}

