//Public domain :)

#ifdef _TINSPIRE
#include <os.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif
#include "SquareLib/SquareLib.h"
#include "Defines.h"

struct SquareCells
{
   int m_nLastError;
};

int SquareLibCreate(SquareLib* api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = malloc(sizeof(struct SquareCells));
   if( pS == NULL ){//Out of memory
      return SQUARELIB_OUT_OF_MEMORY;
   }

   *api = pS;

   return SQUARELIB_OK;
}

int SquareLibFree(SquareLib* api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = *api;

   free(pS);
   *api = NULL;
   return SQUARELIB_OK;
}

int GetSquareLibError(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   return pS->m_nLastError;
}

void ClearSquareLibError(SquareLib api)
{
   struct SquareCells* pS;
   DEBUG_FUNC_NAME;

   pS = (struct SquareCells*)api;
   pS->m_nLastError = SQUARELIB_OK;
}

//SquareLib related functions

