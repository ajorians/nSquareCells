#ifdef _TINSPIRE
#include <nspireio/nspireio.h>
#else
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#endif
#include "SquareLib/SquareLib.h"

#ifdef _TINSPIRE
#define PRINT  nio_printf
#else
#define PRINT  printf
#endif

#ifdef _TINSPIRE
#define PRINT_FUNC PRINT("%s", __func__);
#else
#define PRINT_FUNC PRINT("%s", __FUNCTION__);
#endif

#define TEST_SUCCEEDED	(0)
#define TEST_FAILED	(1)

#define TEST_PERSISTING

#if 0
#ifdef _TINSPIRE
int g_nRelocatedGlobals = 0;
#endif
#endif

int TestConstruction()
{
   SquareLib api;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api) )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

typedef int (*testfunc)();
   testfunc g_Tests[] =
   {
      TestConstruction,
   };

void RunTests()
{
#if 0
#ifdef _TINSPIRE
   if( !g_nRelocatedGlobals ) {
      nl_relocdata((unsigned*)g_Tests, sizeof(g_Tests)/sizeof(g_Tests[0]));
      g_nRelocatedGlobals = 1;
   }
#endif
#endif

   unsigned i;
   for(i=0; i<sizeof(g_Tests)/sizeof(testfunc); i++) {

      int nRet = g_Tests[i]();
      if( nRet == TEST_SUCCEEDED ) {
         PRINT("........OK\n");
      } else {
         PRINT("........FAIL\n");
      }
   }
}


