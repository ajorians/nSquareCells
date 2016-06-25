#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Help.h"

void CreateHelp(struct Help** ppHelp, struct Config* pConfig)
{
   *ppHelp = malloc(sizeof(struct Help));
   struct Help* pHelp = (*ppHelp);

   pHelp->m_pBackground = NULL;
   CreateBackground(&pHelp->m_pBackground, pConfig);

   //pHelp->m_pConfig = pConfig;
}

void FreeHelp(struct Help** ppHelp)
{
   struct Help* pHelp = *ppHelp;
   FreeBackground(&pHelp->m_pBackground);

   //pHelp->m_pConfig = NULL;//Does not own

   free(*ppHelp);
   *ppHelp = NULL;
}

int HelpLoop(struct Help* pHelp)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   DrawBackground(pHelp->m_pBackground, &gc);

   gui_gc_setColorRGB(gc, 0, 0, 0);

   char* strMenu = "H\0e\0l\0p\0\0";
   gui_gc_setFont(gc, Regular12);
   gui_gc_drawString(gc, strMenu, 120, 5, GC_SM_TOP);

   char* pstrHelp[] = { {"This is a logic game."},
{""},
{"Every spot must be marked if it fits the pattern"},
{"or removed if it doesn't fit the pattern."},
{""},
{"The number (if any) to the sides describes the pattern."},
{"Numbers in backets mean that many items are in that row/column"},
{"Otherwise the numbers mean there is that many in a sequence"},
{"with a gap of one of more between the next number."},
{""},
{"Good luck!"}};

   for(int i=0; i<sizeof(pstrHelp)/sizeof(pstrHelp[0]); i++) {
      char buffer[1024];
      ascii2utf16(buffer, pstrHelp[i], 1024);
      gui_gc_setFont(gc, SerifRegular7);
      gui_gc_drawString(gc, buffer, 10, 25+i*15, GC_SM_TOP);
   }

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);

   if( isKeyPressed(KEY_NSPIRE_ESC) ) {
      wait_no_key_pressed();
      return 0;
   }

   return 1;
}


