#ifndef PIECE_H
#define PIECE_H

#include <ngc.h>
#include <SquareLib/SquareLib.h>

struct Metrics;

struct Piece
{
   int m_nX;
   int m_nY;
   int m_nPieceMistaken;
   struct Metrics* m_pMetrics;//Does not own
   SquareLib m_Square;//Does not own
   int m_nColorIndex;
};

void CreatePiece(struct Piece* pPiece, int x, int y, SquareLib pSquare, struct Metrics* pMetrics, int nColorIndex);
void FreePiece(struct Piece* ppPiece);
void PieceDraw(struct Piece* pPiece, Gc* gc);
void PieceMistaken(struct Piece* pPiece);

#endif

