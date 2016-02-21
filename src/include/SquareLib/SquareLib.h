#ifndef SQUARELIB_H_INCLUDED
#define SQUARELIB_H_INCLUDED

typedef void* SquareLib;

#define SQUARELIB_OK			(0)
#define SQUARELIB_BADARGUMENT		(-1)
#define SQUARELIB_OUT_OF_MEMORY		(-2)
#define SQUARELIB_NOT_PUZZLE_FILE	(-3)

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

#endif
