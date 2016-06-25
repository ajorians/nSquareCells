#include <os.h>
#include "StarDrawer.h"

#define STAR_LENGTH	(55)

void CreateStarDrawer(struct StarDrawer** ppDrawer)
{
   *ppDrawer = malloc(sizeof(struct StarDrawer));
   struct StarDrawer* pDrawer = (*ppDrawer);
   pDrawer->arrStar[0] = 125;
   pDrawer->arrStar[1] = pDrawer->arrStar[0] + STAR_LENGTH;
   pDrawer->arrStar[2] = pDrawer->arrStar[1] + 2*STAR_LENGTH;
}

void FreeStarDrawer(struct StarDrawer** ppDrawer)
{
   free(*ppDrawer);
   *ppDrawer = NULL;
}

typedef struct {
   unsigned int x;
   unsigned int y;
} point2D;
void DrawStar(Gc* pgc, int x, int y, int a)
{
   point2D points[] = {{a/2.0+x, -0.16246*a+y},
                   {0.190983*a+x, 0.0620541*a+y},
                   {0.309017*a+x, 0.425325*a+y},
                   {0+x, 0.200811*a+y},
                   {-0.309017*a+x, 0.425325*a+y},
                   {-0.190983*a+x, 0.0620541*a+y},
                   {-a/2.0+x, -0.16246*a+y},
                   {-0.118034*a+x, -0.16246*a+y},
                   {0+x, -0.525731*a+y},
                   {0.118034*a+x, -0.16246*a+y},
                   {a/2.0+x, -0.16246*a+y}};

   gui_gc_setColorRGB(*pgc, 255,215,0);
   gui_gc_fillPoly(*pgc, (unsigned*)points, sizeof (points) / sizeof (points[0]));
}

void DrawStars(struct StarDrawer* pDrawer, Gc* pgc, int nStars, int y)
{
   int a = STAR_LENGTH;
   int nGapX = 5;
   int nStarX = (SCREEN_WIDTH-((nStars-1)*(a+nGapX)))/2;
   for(int i=0; i<nStars; i++) {
      if( pDrawer->arrStar[i] > 0 ) pDrawer->arrStar[i]--;
      int x = nStarX + (nGapX+a)*i + pDrawer->arrStar[i];
      //printf("Star %d: %d,%d\n", i, x, y);
      DrawStar(pgc, x, y+(a/2), a);
   }
}
