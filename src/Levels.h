#ifndef LEVELS_H
#define LEVELS_H

//Indicator Types: 0=NoNumber, 1=Sequential, 2=FullNumbers
//Format SquareCells Version1 Width Height TopIndicatorTypeNumbers LeftIndicatorTypeNumbers X Y IsBomb Value "Summary"
#define LEVEL_1  "SquareCells 1 4 4 1 1 0 0 1 1 1 1 1 0 1 0 1 1 1 0 1 2 1 0 1 3 1 0 2 3 1 0 3 3 1 0 \"Reveal the pattern by removing squares from the grid\rNumbers on the outside of the grid show how many squares in that row/column are part of the pattern\rCtrl to remove an empty, Shift to mark it as part of the pattern\""

#define LEVEL_2  "SquareCells 1 4 4 1 1 1 1 1 1 1 0 3 0 1 0 1 1 1 0 2 1 1 0 3 1 1 0 0 2 1 0 1 2 1 0 2 2 1 0 3 2 1 0 3 3 1 0 \"\""

#define LEVEL_3  "SquareCells 1 4 4 1 1 1 1 1 0 1 0 0 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 3 1 1 0 0 2 1 0 2 2 1 0 0 3 1 0 1 3 1 0 2 3 1 0 3 3 1 0 \"\""

#define LEVEL_4  "SquareCells 1 4 4 1 1 1 0 1 1 1 1 1 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 1 2 1 0 2 2 1 0 3 2 1 0 0 3 1 0 2 3 1 0 \"\""

#define LEVEL_5  "SquareCells 1 4 4 0 0 0 0 0 0 0 0 0 0 1 2 2 0 1 1 0 1 1 0 3 1 1 0 2 2 1 0 3 2 1 4 0 3 1 2 1 3 1 0 3 3 1 0 \"\""

#define LEVEL_6  "SquareCells 1 6 6 0 0 0 0 1 1 0 0 0 1 1 0 0 0 1 4 2 0 1 1 0 1 1 0 1 1 1 0 4 1 1 2 5 1 1 0 1 2 1 0 3 2 1 7 0 3 1 1 3 3 1 0 4 3 1 0 1 4 1 0 4 4 1 0 0 5 1 3 1 5 1 0 3 5 1 0 4 5 1 0 5 5 1 0 \"\""

#define LEVEL_7  "SquareCells 1 6 6 1 0 1 1 1 1 1 1 1 1 1 1 0 0 1 0 2 0 1 7 3 0 1 0 0 1 1 0 1 1 1 0 2 1 1 0 4 1 1 0 2 2 1 0 4 2 1 4 5 2 1 0 0 3 1 0 1 3 1 0 4 3 1 0 0 4 1 0 1 4 1 0 2 4 1 0 5 4 1 0 0 5 1 7 1 5 1 0 3 5 1 4 4 5 1 0 5 5 1 4 \"\""

#define LEVEL_8  "SquareCells 1 6 6 1 0 1 0 1 0 1 0 1 1 0 0 3 0 1 0 4 0 1 4 5 0 1 0 1 1 1 6 4 1 1 0 0 2 1 0 1 2 1 0 2 2 1 0 5 2 1 4 0 3 1 0 2 3 1 0 4 3 1 0 5 3 1 0 4 4 1 4 \"\""

#define LEVEL_9  "SquareCells 1 8 8 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 0 1 0 1 0 3 0 1 0 4 0 1 0 6 0 1 0 7 0 1 0 2 1 1 0 4 1 1 0 5 1 1 0 0 2 1 0 1 2 1 0 3 2 1 0 6 2 1 0 0 3 1 0 2 3 1 0 5 3 1 0 6 3 1 0 7 3 1 0 0 4 1 0 3 4 1 0 7 4 1 0 1 5 1 0 6 5 1 0 0 6 1 0 2 6 1 0 4 6 1 0 5 6 1 0 7 6 1 0 0 7 1 0 3 7 1 0 4 7 1 0 6 7 1 0 \"\""

#define LEVEL_10 "SquareCells 1 6 6 1 0 0 0 1 0 1 0 0 0 0 1 0 0 1 0 3 0 1 0 4 0 1 0 0 1 1 0 1 1 0 3 3 1 1 3 2 2 1 1 5 2 1 0 0 3 1 7 1 3 1 0 3 3 1 1 5 3 1 2 0 4 1 0 1 4 1 0 2 4 1 0 4 4 1 3 1 5 1 0 2 5 1 0 4 5 1 0 5 5 1 0 \"\""

#define LEVEL_11 "SquareCells 1 6 6 1 1 0 1 1 0 0 1 1 0 1 0 1 0 1 0 3 0 1 0 4 0 1 0 0 1 1 0 2 1 1 0 3 1 1 6 4 1 1 0 1 2 1 5 3 2 1 0 5 2 1 0 1 3 1 0 2 3 1 0 4 3 1 0 5 3 1 0 0 4 1 5 1 4 1 0 3 4 1 0 4 4 1 7 3 5 1 0 4 5 1 0 \"\""

#define LEVEL_12 "SquareCells 1 4 4 0 0 0 0 0 0 0 0 0 0 1 2 1 0 1 0 3 0 1 0 2 1 1 0 0 2 1 0 1 2 1 4 3 2 1 0 0 3 1 0 1 3 1 0 3 3 1 2 \"\""

#define LEVEL_13 "SquareCells 1 4 4 2 0 2 0 2 0 2 2 0 0 1 0 1 0 1 0 3 0 1 0 0 1 1 0 2 0 1 0 0 2 1 0 2 2 1 2 0 3 1 0 1 3 1 0 3 3 1 0 \"Numbers inside brackets only show the total for that row or column, not the grouping.\""

#define LEVEL_14 "SquareCells 1 4 4 2 0 2 2 0 2 1 0 1 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 0 2 1 0 1 2 1 0 0 3 1 4 2 3 1 2 3 3 1 0 \"\""

#define LEVEL_15 "SquareCells 1 6 6 0 2 2 2 2 0 2 2 2 0 2 2 0 0 1 0 1 0 1 3 3 0 1 0 4 0 1 3 5 0 1 0 1 1 1 0 0 2 1 0 2 2 1 0 3 2 1 0 5 2 1 7 0 3 1 2 2 3 1 0 3 3 1 0 4 3 1 0 5 3 1 0 1 4 1 0 1 5 1 2 4 5 1 2 5 5 1 0 \"\""

#define LEVEL_16 "SquareCells 1 6 6 2 2 2 2 0 2 1 1 0 0 1 1 3 0 1 0 5 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 2 2 1 0 4 2 1 2 5 2 1 0 0 3 1 0 1 3 1 2 3 3 1 0 2 4 1 0 3 4 1 0 4 4 1 0 5 4 1 0 1 5 1 0 2 5 1 0 3 5 1 0 \"\""

#define LEVEL_17 "SquareCells 1 8 8 0 0 2 2 0 0 0 2 0 1 0 2 2 2 0 1 0 0 1 3 2 0 1 0 3 0 1 6 4 0 1 6 5 0 1 0 7 0 1 2 0 1 1 0 1 1 1 0 3 1 1 0 4 1 1 0 7 1 1 0 2 2 1 1 5 2 1 2 0 3 1 2 1 3 1 0 3 3 1 0 5 3 1 0 7 3 1 0 3 4 1 2 7 4 1 0 1 5 1 0 2 5 1 2 4 5 1 0 5 5 1 2 7 5 1 0 0 7 1 0 1 7 1 2 4 7 1 0 5 7 1 0 6 7 1 4 7 7 1 0 \"\""

#define LEVEL_18 "SquareCells 1 4 4 0 2 1 0 0 0 0 0 0 0 1 0 2 0 1 0 3 0 1 0 0 1 1 0 2 1 1 6 3 1 1 0 0 2 1 0 1 2 1 6 3 2 1 0 0 3 1 0 1 3 1 0 3 3 1 0 \"\""

#define LEVEL_19 "SquareCells 1 8 8 2 1 1 2 2 1 1 1 2 2 2 2 1 0 0 1 0 0 1 3 0 1 1 0 0 3 1 0 0 4 1 0 0 5 1 0 1 0 1 0 1 2 1 0 1 5 1 0 1 7 1 0 2 2 1 0 2 5 1 0 2 7 1 0 3 0 1 2 3 2 1 0 3 4 1 10 3 5 1 0 4 0 1 0 4 2 1 0 4 3 1 10 4 5 1 0 4 7 1 0 5 2 1 0 5 5 1 0 5 7 1 0 6 0 1 0 6 2 1 0 6 5 1 0 7 2 1 0 7 3 1 0 7 4 1 0 7 6 1 0 7 7 1 2 \"\""

#define LEVEL_33 "SquareCells 1 4 4 0 2 1 2 0 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 2 2 1 0 1 3 1 0 3 3 1 0 \"\""

void LevelLoad(char* pstr, int nLevelNum);

#endif

