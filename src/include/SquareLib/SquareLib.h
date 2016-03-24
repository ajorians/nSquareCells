#ifndef SQUARELIB_H_INCLUDED
#define SQUARELIB_H_INCLUDED

typedef void* SquareLib;

#define SQUARELIB_OK			(0)
#define SQUARELIB_BADARGUMENT		(-1)
#define SQUARELIB_OUT_OF_MEMORY		(-2)
#define SQUARELIB_NOT_PUZZLE_FILE	(-3)

#define SQUARELIB_MARKED		(1)
#define SQUARELIB_NOT_MARKED		(0)

#define SQUARELIB_DESTROYED		(1)
#define SQUARELIB_NOT_DESTROYED		(0)

#define SQUARELIB_GAMEOVER		(1)
#define SQUARELIB_NOT_GAMEOVER		(0)

#define SQUARELIB_NUMBER_VAL_MET	(1)
#define SQUARELIB_NUMBER_VAL_NOTMET	(0)

enum IndicatorType
{
   NoNumber = 0,
   Sequential = 1,
   FullNumbers = 2
};

//////////////////////////////////////////////
//Initalization/Error checking/Mode functions
//////////////////////////////////////////////
int SquareLibCreate(SquareLib* api, const char* pstrFile);
int SquareLibFree(SquareLib* api);

int GetSquareLibError(SquareLib api);
void ClearSquareLibError(SquareLib api);

//////////////////////////////////////////////
//SquareLib related functions
//////////////////////////////////////////////
int GetSquareWidth(SquareLib api);
int GetSquareHeight(SquareLib api);
int ToggleSquareMark(SquareLib api, int nX, int nY);
int IsSquareMarked(SquareLib api, int nX, int nY, int* pMarked);
int DestroySquare(SquareLib api, int nX, int nY);
int IsSquareDestroyed(SquareLib api, int nX, int nY, int* pDestroyed);
int GetSquaresRemaining(SquareLib api);
int IsSquareGameOver(SquareLib api);
int IsSquareNumberMet(SquareLib api, int nX, int nY);
int GetNumSquareIndicatorsForRow(SquareLib api, int nIndex);
int GetNumSquareIndicatorsForCol(SquareLib api, int nIndex);
int GetSquareIndicatorsForRow(SquareLib api, int nIndex, int arr[8]);
int GetSquareIndicatorsForCol(SquareLib api, int nIndex, int arr[8]);

#endif
