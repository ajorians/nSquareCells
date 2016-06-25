#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <ngc.h>
#include "Config.h"

#define NUM_SQUARES	(15)

struct Square {
   int x;
   int y;
   int size;
   int r;
   int g;
   int b;
   int direction;
   int move;
};

struct Background
{
   struct Square m_ArrSquares[NUM_SQUARES];
   struct Config* m_pConfig;//Does not own
};

void CreateBackground(struct Background** ppBackground, struct Config* pConfig);
void FreeBackground(struct Background** ppBackground);
void DrawBackground(struct Background* pBackground, Gc* pgc);

#endif

