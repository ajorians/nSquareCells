#include <os.h>
#include <libndls.h>
#include <ngc.h>
#include "Options.h"

void CreateOptions(struct Options** ppOptions, struct Config* pConfig)
{
   *ppOptions = malloc(sizeof(struct Options));
   struct Options* pOptions = (*ppOptions);

   pOptions->m_pBackground = NULL;
   CreateBackground(&pOptions->m_pBackground, pConfig);

   pOptions->m_pConfig = pConfig;
}

void FreeOptions(struct Options** ppOptions)
{
   struct Options* pOptions = *ppOptions;
   FreeBackground(&pOptions->m_pBackground);

   pOptions->m_pConfig = NULL;//Does not own

   free(*ppOptions);
   *ppOptions = NULL;
}

int OptionsLoop(struct Options* pOptions)
{
   Gc gc = gui_gc_global_GC();

   gui_gc_begin(gc);

   DrawBackground(pOptions->m_pBackground, &gc);

   gui_gc_setColorRGB(gc, 0, 0, 0);

   char* strMenu = "O\0p\0t\0i\0o\0n\0s\0\0";
   gui_gc_drawString(gc, strMenu, 120, 5, GC_SM_TOP);

   char* strDrawBackgroundOn = "D\0r\0a\0w\0 \0b\0a\0c\0k\0g\0r\0o\0u\0n\0d\0:\0 \0O\0n\0\0";
   char* strDrawBackgroundOff = "D\0r\0a\0w\0 \0b\0a\0c\0k\0g\0r\0o\0u\0n\0d\0:\0 \0O\0f\0f\0\0";
   gui_gc_drawString(gc, GetDrawBackground(pOptions->m_pConfig) ? strDrawBackgroundOn : strDrawBackgroundOff, 50, 50, GC_SM_TOP);
   if( 1 /*pMenu->m_eChoice == Options*/ ) {
      gui_gc_setColorRGB(gc, 255, 0, 0);
      gui_gc_drawRect(gc, 50-2, 50-2, 165, 20);
   }

   gui_gc_blit_to_screen(gc);
   gui_gc_finish(gc);

   if( isKeyPressed(KEY_NSPIRE_ESC) ) {
      wait_no_key_pressed();
      return 0;
   }

   if( isKeyPressed(KEY_NSPIRE_ENTER) ) {
      wait_no_key_pressed();
      SetDrawBackground(pOptions->m_pConfig, !GetDrawBackground(pOptions->m_pConfig));
   }

   return 1;
}


