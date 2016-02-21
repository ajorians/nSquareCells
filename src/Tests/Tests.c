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

#define LEVEL_33 "SQUARECELLS 1 8 4 4 0 2 1 2 0 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 2 2 1 0 1 3 1 0 3 3 1 0"

int TestConstruction()
{
   SquareLib api;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestWidthAndHeight()
{
   SquareLib api;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   if( 4 != GetSquareWidth(&api) )
      return TEST_FAILED;

   if( 4 != GetSquareHeight(&api) )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

typedef int (*testfunc)();
   testfunc g_Tests[] =
   {
      TestConstruction,
      TestWidthAndHeight
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


