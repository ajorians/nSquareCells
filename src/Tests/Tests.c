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

//SquareCells VerNum Width Height
//Across top type for each column
//Across left type for each row
//x y IsBomb IsDestroyed
#define LEVEL_33 "SquareCells 1 4 4 0 2 1 2 0 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 2 2 1 0 1 3 1 0 3 3 1 0 \"\""

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

   if( 4 != GetSquareWidth(api) )
      return TEST_FAILED;

   if( 4 != GetSquareHeight(api) )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestCellsRemaining()
{
   SquareLib api;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   if( 8 != GetSquaresRemaining(api) )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;
   
   return TEST_SUCCEEDED;
}

int TestSimpleMarking()
{
   SquareLib api;
   int nMarked = 0;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   if( SQUARELIB_OK != ToggleSquareMark(api, 0, 0) )
      return TEST_FAILED;

   if( SQUARELIB_OK != IsSquareMarked(api, 0, 0, &nMarked) )
      return TEST_FAILED;

   if( SQUARELIB_MARKED != nMarked )
      return TEST_FAILED;

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestGameOver()
{
   SquareLib api;
   unsigned int i;
   PRINT_FUNC;
   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   if( SQUARELIB_NOT_GAMEOVER != IsSquareGameOver(api) )
      return TEST_FAILED;

   if( 8 != GetSquaresRemaining(api) ) {
      printf("Wrong number of squares remaining from get-go: %d\n", GetSquaresRemaining(api));
      return TEST_FAILED;
   }

   int aMarkings[][2] = {
      { 0, 0 },
      { 1, 0 },
      { 2, 0 },
      { 3, 0 },
      { 1, 1 },
      { 2, 2 },
      { 1, 3 },
      { 3, 3 }
   };
   for(i=0; i<sizeof(aMarkings)/sizeof(aMarkings[0]); i++) {
      if( SQUARELIB_OK != ToggleSquareMark(api, aMarkings[i][0], aMarkings[i][1]) ) {
         printf("Unable to mark spot %d,%d\n", aMarkings[i][0], aMarkings[i][1]);
         return TEST_FAILED;
      }

      if( SQUARELIB_NOT_GAMEOVER != IsSquareGameOver(api) ) {
         printf("Shouldn't be game over for %d\n", i);
         return TEST_FAILED;
      }
   }

   if( 8 != GetSquaresRemaining(api) ) {
      printf("Wrong number of squares remaining: %d\n", GetSquaresRemaining(api));
      return TEST_FAILED;
   }

   int aDestroy[][2] = {
      { 0, 1 },
      { 2, 1 },
      { 3, 1 },
      { 0, 2 },
      { 1, 2 },
      { 3, 2 },
      { 0, 3 },
      { 2, 3 }
   };
   for(i=0; i<sizeof(aMarkings)/sizeof(aMarkings[0]); i++) {
      if( SQUARELIB_OK != DestroySquare(api, aDestroy[i][0], aDestroy[i][1]) ) {
         printf("Unable to destroy square at %d,%d\n", aDestroy[i][0], aDestroy[i][1]);
         return TEST_FAILED;
      }

      if( i+1 < sizeof(aMarkings)/sizeof(aMarkings[0]) ) {
         if( SQUARELIB_NOT_GAMEOVER != IsSquareGameOver(api) ) {
            printf("Shouldn't be game over for %d\n", i);
            return TEST_FAILED;
         }
      }

      if( 8-(i+1) != GetSquaresRemaining(api) ) {
         printf("Expected squares remaining: %d; actual: %d\n", 8-(i+1), GetSquaresRemaining(api));
         return TEST_FAILED;
      }
   }

   if( SQUARELIB_GAMEOVER != IsSquareGameOver(api) ) {
      printf("Expected game over\n");
      return TEST_FAILED;
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;
   
   return TEST_SUCCEEDED;
}

int TestIndicatorCount()
{
   SquareLib api;
   unsigned int i;
   PRINT_FUNC;

   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   int arrColExp[] = { 0, 1, 2, 1 };

   for(i=0; i<sizeof(arrColExp)/sizeof(arrColExp[0]); i++) {
      if( arrColExp[i] != GetNumSquareIndicatorsForCol(api, i) ) {
         printf("Col %d, expected: %d; got %d\n", i, arrColExp[i], GetNumSquareIndicatorsForCol(api, i));
         return TEST_FAILED;
      }
   }

   int arrRowExp[] = { 0, 1, 1, 2 };

   for(i=0; i<sizeof(arrRowExp)/sizeof(arrRowExp[0]); i++) {
      if( arrRowExp[i] != GetNumSquareIndicatorsForRow(api, i) ) {
         printf("Row %d, expected: %d; got %d\n", i, arrRowExp[i], GetNumSquareIndicatorsForRow(api, i));
         return TEST_FAILED;
      }
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestIndicators()
{
   SquareLib api;
   int arr[8];
   unsigned int i;
   PRINT_FUNC;

   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   int arrColExp[] = { 0, 1, 2, 1 };

   for(i=0; i<sizeof(arrColExp)/sizeof(arrColExp[0]); i++) {
      if( arrColExp[i] != GetSquareIndicatorsForCol(api, i, arr) ) {
         printf("Col %d, expected: %d; got %d\n", i, arrColExp[i], GetSquareIndicatorsForCol(api, i, arr));
         return TEST_FAILED;
      }
   }

   int arrRowExp[] = { 0, 1, 1, 2 };

   for(i=0; i<sizeof(arrRowExp)/sizeof(arrRowExp[0]); i++) {
      if( arrRowExp[i] != GetSquareIndicatorsForRow(api, i, arr) ) {
         printf("Row %d, expected: %d; got %d\n", i, arrRowExp[i], GetSquareIndicatorsForRow(api, i, arr));
         return TEST_FAILED;
      }
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

int TestIndicatorsTypes()
{
   SquareLib api;
   unsigned int i;
   PRINT_FUNC;

   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_33) )
      return TEST_FAILED;

   enum IndicatorType arrColTypes[] = { NoNumber, FullNumbers, Sequential, FullNumbers };

   for(i=0; i<sizeof(arrColTypes)/sizeof(arrColTypes[0]); i++) {
      enum IndicatorType eType;
      if( GetSquareIndicatorTypeRow(api, i, &eType) != SQUARELIB_OK ) {
         printf("Col %d, expected: %d; got %d\n", i, arrColTypes[i], eType);
         return TEST_FAILED;
      }
   }

   enum IndicatorType arrRowTypes[] = { NoNumber, Sequential, Sequential, Sequential };

   for(i=0; i<sizeof(arrRowTypes)/sizeof(arrRowTypes[0]); i++) {
      enum IndicatorType eType;
      if( GetSquareIndicatorTypeCol(api, i, &eType) != SQUARELIB_OK ) {
         printf("Row %d, expected: %d; got %d\n", i, arrRowTypes[i], eType);
         return TEST_FAILED;
      }
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

#define LEVEL_5  "SquareCells 1 4 4 0 0 0 0 0 0 0 0 0 0 1 2 2 0 1 1 0 1 1 0 3 1 1 0 2 2 1 0 3 2 1 4 0 3 1 2 1 3 1 0 3 3 1 0 \"\""

int TestSpotNumbers()
{
   SquareLib api;
   unsigned int x,y,i;
   PRINT_FUNC;

   if( SQUARELIB_OK != SquareLibCreate(&api, LEVEL_5) )
      return TEST_FAILED;

   int aSpotsWithNumbers[][3] = {
      { 0, 0, 2 },
      { 2, 0, 1 },
      { 3, 2, 4 },
      { 0, 3, 2 }
   };

   for(x=0; x<GetSquareWidth(api); x++) {
      for(y=0; y<GetSquareHeight(api); y++) {
         int nSpotValue = 0;
         int nHasSpot = GetSpotNumber(api, x, y, &nSpotValue);
         int nShouldHaveSpot = 0;
         int nExpectedSpotValue = 0;
         for(i=0; i<sizeof(aSpotsWithNumbers)/sizeof(aSpotsWithNumbers[0]); i++) {
            if( aSpotsWithNumbers[i][0] == x && aSpotsWithNumbers[i][1] == y ) {
               nShouldHaveSpot = 1;
               nExpectedSpotValue = aSpotsWithNumbers[i][2];
            }
         }

         if( nHasSpot != nShouldHaveSpot )
            return TEST_FAILED;
         if( nHasSpot == SQUARELIB_HAS_VALUE && nSpotValue != nExpectedSpotValue )
            return TEST_FAILED;
      }
   }

   if( SQUARELIB_OK != SquareLibFree(&api) )
      return TEST_FAILED;

   return TEST_SUCCEEDED;
}

typedef int (*testfunc)();
   testfunc g_Tests[] =
   {
      TestConstruction,
      TestWidthAndHeight,
      TestCellsRemaining,
      TestSimpleMarking,
      TestGameOver,
      TestIndicatorCount,
      TestIndicators,
      TestIndicatorsTypes,
      TestSpotNumbers
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


