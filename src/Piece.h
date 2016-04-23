#ifndef PIECE_H
#define PIECE_H

#include <ngc.h>
#include <SquareLib/SquareLib.h>

struct Metrics;

struct Piece
{
   int m_nX;
   int m_nY;
   struct Metrics* m_pMetrics;//Does not own
   SquareLib m_Square;//Does not own
};

void CreatePiece(struct Piece* pPiece, int x, int y, SquareLib pSquare, struct Metrics* pMetrics);
void FreePiece(struct Piece* ppPiece);
void PieceDraw(struct Piece* pPiece, Gc* gc);

#endif

