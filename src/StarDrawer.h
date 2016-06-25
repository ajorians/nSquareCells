#ifndef STAR_DRAWER_H
#define STAR_DRAWER_H

#include <ngc.h>

struct StarDrawer
{
   int arrStar[3];
};

void CreateStarDrawer(struct StarDrawer** ppDrawer);
void FreeStarDrawer(struct StarDrawer** ppDrawer);
void DrawStars(struct StarDrawer* pDrawer, Gc* pgc, int nStars, int y);

#endif

