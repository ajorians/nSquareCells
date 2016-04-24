#ifndef SELECTOR_H
#define SELECTOR_H

#include <ngc.h>
#include <SquareLib/SquareLib.h>

struct Metrics;

struct Selector
{
   SquareLib m_Square;//Does not own
   struct Metrics* m_pMetrics;//Does not own
   int m_nSelectionX;
   int m_nSelectionY;
};

enum SelDirection
{
   Sel_Left,
   Sel_Right,
   Sel_Up,
   Sel_Down
};

void CreateSelector(struct Selector** ppSelector, SquareLib square, struct Metrics* pMetrics);
void FreeSelector(struct Selector** ppSelector);
void SelectorDraw(struct Selector* pSelector, Gc* pgc);
void SelectorMove(struct Selector* pSelector, enum SelDirection eDirection);

#endif

