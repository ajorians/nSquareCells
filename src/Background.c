#include <os.h>
#include "Background.h"

#define MOVE_SPEED	(1)

void CreateBackground(struct Background** ppBackground, struct Config* pConfig)
{
   *ppBackground = malloc(sizeof(struct Background));
   struct Background* pBackground = (*ppBackground);
   pBackground->m_pConfig = pConfig;
   for(int i=0; i<NUM_SQUARES; i++) {
      struct Square* pSquare = &pBackground->m_ArrSquares[i];
      pSquare->x = rand()%SCREEN_WIDTH;
      pSquare->y = rand()%SCREEN_WIDTH;
      int nSize = rand()%35+10;
      pSquare->size = nSize;
      pSquare->r = rand()%255;
      pSquare->g = rand()%255;
      pSquare->b = rand()%255;
      pSquare->direction = rand()%2;
      pSquare->move = MOVE_SPEED;
   }
}

void FreeBackground(struct Background** ppBackground)
{
   free(*ppBackground);
   *ppBackground = NULL;
}

void DrawBackground(struct Background* pBackground, Gc* pgc)
{
   gui_gc_setColorRGB(*pgc, 255, 255, 255);
   gui_gc_fillRect(*pgc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   if( GetDrawBackground( pBackground->m_pConfig ) == 0 )
      return;

   for(int i=0; i<NUM_SQUARES; i++) {
      struct Square* pSquare = &pBackground->m_ArrSquares[i];
      gui_gc_setColorRGB(*pgc, pSquare->r, pSquare->g, pSquare->b);
      gui_gc_drawRect(*pgc, pSquare->x, pSquare->y, pSquare->size, pSquare->size);
      pSquare->move--;
      if( pSquare->move <= 0 ) {
         if( pSquare->direction == 0 ) {
            pSquare->x++;
         } else {
            pSquare->y++;
         }

         pSquare->move = MOVE_SPEED;
      }

      if( pSquare->x > SCREEN_WIDTH ) {
         pSquare->x = -pSquare->size;
      }
      if( pSquare->y > SCREEN_HEIGHT ) {
         pSquare->y = -pSquare->size;
      }

   }
}
