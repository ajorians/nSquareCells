#ifndef LEVELS_H
#define LEVELS_H

//Indicator Types: 0=NoNumber, 1=Sequential, 2=FullNumbers
//Format SquareCells Version1 Width Height TopIndicatorTypeNumbers LeftIndicatorTypeNumbers X Y IsBomb Value "Summary"
#define LEVEL_1  "SquareCells 1 4 4 1 1 0 0 1 1 1 1 1 0 1 0 1 1 1 0 1 2 1 0 1 3 1 0 2 3 1 0 3 3 1 0 \"Reveal the pattern by removing squares from the grid\n\nNumbers on the outside of the grid show how many squares in that row/column are part of the pattern\n\nCtrl to remove an empty, Shift to mark it as part of the pattern\""

#define LEVEL_2  "SquareCells 1 4 4 1 1 1 1 1 1 1 0 3 0 1 0 1 1 1 0 2 1 1 0 3 1 1 0 0 2 1 0 1 2 1 0 2 2 1 0 3 2 1 0 3 3 1 0 \"\""

#define LEVEL_3  "SquareCells 1 4 4 1 1 1 1 1 0 1 0 0 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 3 1 1 0 0 2 1 0 2 2 1 0 0 3 1 0 1 3 1 0 2 3 1 0 3 3 1 0 \"\""

#define LEVEL_4  "SquareCells 1 4 4 1 1 1 0 1 1 1 1 1 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 1 2 1 0 2 2 1 0 3 2 1 0 0 3 1 0 2 3 1 0 \"\""

#define LEVEL_5  "SquareCells 1 4 4 0 0 0 0 0 0 0 0 0 0 1 2 2 0 1 1 0 1 1 0 3 1 1 0 2 2 1 0 3 2 1 4 0 3 1 2 1 3 1 0 3 3 1 0 \"A number inside a square shows it is part of a group of connected squares of that size.\n\nSquares do not connect diagonally.\""

#define LEVEL_6  "SquareCells 1 6 6 0 0 0 0 1 1 0 0 0 1 1 0 0 0 1 4 2 0 1 1 0 1 1 0 1 1 1 0 4 1 1 2 5 1 1 0 1 2 1 0 3 2 1 7 0 3 1 1 3 3 1 0 4 3 1 0 1 4 1 0 4 4 1 0 0 5 1 3 1 5 1 0 3 5 1 0 4 5 1 0 5 5 1 0 \"\""

#define LEVEL_7  "SquareCells 1 6 6 1 0 1 1 1 1 1 1 1 1 1 1 0 0 1 0 2 0 1 7 3 0 1 0 0 1 1 0 1 1 1 0 2 1 1 0 4 1 1 0 2 2 1 0 4 2 1 4 5 2 1 0 0 3 1 0 1 3 1 0 4 3 1 0 0 4 1 0 1 4 1 0 2 4 1 0 5 4 1 0 0 5 1 7 1 5 1 0 3 5 1 4 4 5 1 0 5 5 1 4 \"\""

#define LEVEL_8  "SquareCells 1 6 6 1 0 1 0 1 0 1 0 1 1 0 0 3 0 1 0 4 0 1 4 5 0 1 0 1 1 1 6 4 1 1 0 0 2 1 0 1 2 1 0 2 2 1 0 5 2 1 4 0 3 1 0 2 3 1 0 4 3 1 0 5 3 1 0 4 4 1 4 \"\""

#define LEVEL_9  "SquareCells 1 8 8 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 0 1 0 1 0 3 0 1 0 4 0 1 0 6 0 1 0 7 0 1 0 2 1 1 0 4 1 1 0 5 1 1 0 0 2 1 0 1 2 1 0 3 2 1 0 6 2 1 0 0 3 1 0 2 3 1 0 5 3 1 0 6 3 1 0 7 3 1 0 0 4 1 0 3 4 1 0 7 4 1 0 1 5 1 0 6 5 1 0 0 6 1 0 2 6 1 0 4 6 1 0 5 6 1 0 7 6 1 0 0 7 1 0 3 7 1 0 4 7 1 0 6 7 1 0 \"\""

#define LEVEL_10 "SquareCells 1 6 6 1 0 0 0 1 0 1 0 0 0 0 1 0 0 1 0 3 0 1 0 4 0 1 0 0 1 1 0 1 1 1 3 3 1 1 3 2 2 1 1 5 2 1 0 0 3 1 7 1 3 1 0 3 3 1 1 5 3 1 2 0 4 1 0 1 4 1 0 2 4 1 0 4 4 1 3 1 5 1 0 2 5 1 0 4 5 1 0 5 5 1 0 \"\""

#define LEVEL_11 "SquareCells 1 6 6 1 1 0 1 1 0 0 1 1 0 1 0 1 0 1 0 3 0 1 0 4 0 1 0 0 1 1 0 2 1 1 0 3 1 1 6 4 1 1 0 1 2 1 5 3 2 1 0 5 2 1 0 1 3 1 0 2 3 1 0 4 3 1 0 5 3 1 0 0 4 1 5 1 4 1 0 3 4 1 0 4 4 1 7 3 5 1 0 4 5 1 0 \"\""

#define LEVEL_12 "SquareCells 1 4 4 0 0 0 0 0 0 0 0 0 0 1 2 1 0 1 0 3 0 1 0 2 1 1 0 0 2 1 0 1 2 1 4 3 2 1 0 0 3 1 0 1 3 1 0 3 3 1 2 \"\""

#define LEVEL_13 "SquareCells 1 4 4 2 0 2 0 2 0 2 2 0 0 1 0 1 0 1 0 3 0 1 0 0 1 1 0 2 1 1 0 0 2 1 0 2 2 1 2 0 3 1 0 1 3 1 0 3 3 1 0 \"Numbers inside brackets only show the total for that row or column, not the grouping.\""

#define LEVEL_14 "SquareCells 1 4 4 2 0 2 2 0 2 1 0 1 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 0 2 1 0 1 2 1 0 0 3 1 4 2 3 1 2 3 3 1 0 \"\""

#define LEVEL_15 "SquareCells 1 6 6 0 2 2 2 2 0 2 2 2 0 2 2 0 0 1 0 1 0 1 3 3 0 1 0 4 0 1 3 5 0 1 0 1 1 1 0 0 2 1 0 2 2 1 0 3 2 1 0 5 2 1 7 0 3 1 2 2 3 1 0 3 3 1 0 4 3 1 0 5 3 1 0 1 4 1 0 1 5 1 2 4 5 1 2 5 5 1 0 \"\""

#define LEVEL_16 "SquareCells 1 6 6 2 2 2 2 0 2 1 1 0 0 1 1 3 0 1 0 5 0 1 0 0 1 1 0 2 1 1 0 3 1 1 0 2 2 1 0 4 2 1 2 5 2 1 0 0 3 1 0 1 3 1 2 3 3 1 0 2 4 1 0 3 4 1 0 4 4 1 0 5 4 1 0 1 5 1 0 2 5 1 0 3 5 1 0 \"\""

#define LEVEL_17 "SquareCells 1 8 8 0 0 2 2 0 0 0 2 0 1 0 2 2 2 0 1 0 0 1 3 2 0 1 0 3 0 1 6 4 0 1 6 5 0 1 0 7 0 1 2 0 1 1 0 1 1 1 0 3 1 1 0 4 1 1 0 7 1 1 0 2 2 1 1 5 2 1 2 0 3 1 2 1 3 1 0 3 3 1 0 5 3 1 0 7 3 1 0 3 4 1 2 7 4 1 0 1 5 1 0 2 5 1 2 4 5 1 0 5 5 1 2 7 5 1 0 0 7 1 0 1 7 1 2 4 7 1 0 5 7 1 0 6 7 1 4 7 7 1 0 \"\""

#define LEVEL_18 "SquareCells 1 4 4 0 2 1 0 0 0 0 0 0 0 1 0 2 0 1 0 3 0 1 0 0 1 1 0 2 1 1 6 3 1 1 0 0 2 1 0 1 2 1 6 3 2 1 0 0 3 1 0 1 3 1 0 3 3 1 0 \"\""

#define LEVEL_19 "SquareCells 1 8 8 2 1 1 2 2 1 1 1 2 2 2 2 1 0 0 1 0 0 1 3 0 1 1 0 0 3 1 0 0 4 1 0 0 5 1 0 1 0 1 0 1 2 1 0 1 5 1 0 1 7 1 0 2 2 1 0 2 5 1 0 2 7 1 0 3 0 1 2 3 2 1 0 3 4 1 10 3 5 1 0 4 0 1 0 4 2 1 0 4 3 1 10 4 5 1 0 4 7 1 0 5 2 1 0 5 5 1 0 5 7 1 0 6 0 1 0 6 2 1 0 6 5 1 0 7 2 1 0 7 3 1 0 7 4 1 0 7 6 1 0 7 7 1 2 \"\""

#define LEVEL_20 "SquareCells 1 10 10 0 1 1 1 1 1 1 1 1 0 0 1 2 1 1 1 1 2 1 0 0 0 1 2 1 0 1 0 3 0 1 0 4 0 1 0 5 0 1 0 6 0 1 0 7 0 1 0 9 0 1 2 3 1 1 0 4 1 1 0 5 1 1 0 6 1 1 0 9 1 1 0 3 2 1 0 4 2 1 0 5 2 1 0 6 2 1 0 0 3 1 0 1 3 1 0 2 3 1 0 4 3 1 0 7 3 1 0 8 3 1 0 9 3 1 0 0 4 1 0 1 4 1 0 2 4 1 0 4 4 1 0 7 4 1 0 8 4 1 0 9 4 1 0 0 5 1 0 1 5 1 0 2 5 1 0 5 5 1 0 7 5 1 0 8 5 1 0 9 5 1 0 0 6 1 0 1 6 1 0 2 6 1 0 5 6 1 0 7 6 1 0 8 6 1 0 9 6 1 0 3 7 1 0 4 7 1 0 5 7 1 0 6 7 1 0 0 8 1 0 3 8 1 0 4 8 1 0 5 8 1 0 6 8 1 0 0 9 1 2 2 9 1 0 3 9 1 0 4 9 1 0 5 9 1 0 6 9 1 0 8 9 1 0 9 9 1 2 \"\""

#define LEVEL_21 "SquareCells 1 10 10 1 1 2 0 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 0 1 0 2 0 1 0 5 0 1 0 9 0 1 0 0 1 1 0 1 1 1 0 2 1 1 8 3 1 1 0 5 1 1 2 7 1 1 0 8 1 1 5 1 2 1 0 7 2 1 0 8 2 1 0 1 3 1 0 3 3 1 7 4 3 1 0 5 3 1 0 7 3 1 0 9 3 1 0 0 4 1 0 5 4 1 0 6 4 1 0 9 4 1 0 0 5 1 0 1 5 1 4 3 5 1 0 6 5 1 0 9 5 1 0 0 6 1 0 3 6 1 0 4 6 1 5 6 6 1 7 8 6 1 0 1 7 1 4 2 7 1 0 4 7 1 0 8 7 1 5 0 8 1 0 2 8 1 0 4 8 1 0 6 8 1 0 7 8 1 5 8 8 1 0 2 9 1 0 5 9 1 0 9 9 1 0 \"\""

#define LEVEL_22 "SquareCells 1 10 10 1 0 1 1 1 1 1 0 1 1 0 0 1 1 1 1 1 1 0 1 0 0 1 4 1 0 1 0 3 0 1 0 4 0 1 0 5 0 1 0 6 0 1 0 7 0 1 6 9 0 1 0 0 1 1 0 1 1 1 0 4 1 1 0 8 1 1 0 9 1 1 6 2 2 1 15 3 2 1 0 5 2 1 0 6 2 1 10 7 2 1 0 9 2 1 0 2 3 1 0 7 3 1 0 9 3 1 0 0 4 1 0 2 4 1 0 4 4 1 4 5 4 1 0 7 4 1 0 9 4 1 0 0 5 1 0 2 5 1 0 4 5 1 0 5 5 1 0 7 5 1 0 8 5 1 0 1 6 1 0 2 6 1 0 7 6 1 0 9 6 1 0 2 7 1 0 3 7 1 0 4 7 1 0 6 7 1 0 7 7 1 10 0 8 1 0 1 8 1 3 4 8 1 15 5 8 1 0 9 8 1 3 1 9 1 0 4 9 1 0 5 9 1 0 6 9 1 0 8 9 1 0 9 9 1 0 \"\""

#define LEVEL_23 "SquareCells 1 8 8 1 1 1 1 0 1 1 1 1 1 1 0 0 1 1 1 1 0 1 0 2 0 1 4 3 0 1 0 6 0 1 0 1 1 1 0 6 1 1 0 7 1 1 3 0 2 1 0 4 2 1 0 5 2 1 3 0 3 1 2 5 3 1 0 1 4 1 0 2 4 1 0 3 4 1 4 1 5 1 0 4 5 1 3 5 5 1 0 0 6 1 5 4 6 1 0 6 6 1 3 7 6 1 0 0 7 1 0 1 7 1 5 2 7 1 0 3 7 1 0 6 7 1 0 \"\""

#define LEVEL_24 "SquareCells 1 10 10 1 1 1 1 1 2 2 1 1 1 1 2 2 1 1 1 1 0 1 1 0 0 1 0 1 0 1 0 4 0 1 0 6 0 1 0 0 1 1 0 1 1 1 7 4 1 1 0 6 1 1 0 7 1 1 0 8 1 1 0 0 2 1 0 1 2 1 0 2 2 1 0 8 2 1 8 3 3 1 0 6 3 1 8 7 3 1 0 8 3 1 0 0 4 1 0 2 4 1 0 3 4 1 0 4 4 1 5 5 4 1 0 9 4 1 0 0 5 1 0 6 5 1 0 9 5 1 0 1 6 1 0 2 6 1 0 3 6 1 8 6 6 1 0 7 6 1 5 8 6 1 0 1 7 1 8 3 7 1 0 6 7 1 0 1 8 1 0 2 8 1 0 3 8 1 0 0 9 1 0 4 9 1 0 5 9 1 0 6 9 1 0 7 9 1 0 8 9 1 6 9 9 1 0 \"\""

#define LEVEL_25 "SquareCells 1 8 8 0 0 1 1 1 1 0 0 1 0 0 1 1 0 0 1 0 0 1 0 1 0 1 0 4 0 1 0 6 0 1 0 7 0 1 0 0 1 1 0 1 1 1 4 3 1 1 0 6 1 1 4 7 1 1 0 2 2 1 18 3 2 1 0 4 2 1 0 5 2 1 18 0 3 1 0 2 3 1 0 3 3 1 0 4 3 1 0 5 3 1 0 2 4 1 0 3 4 1 0 4 4 1 0 5 4 1 0 7 4 1 0 2 5 1 18 3 5 1 0 4 5 1 0 5 5 1 18 0 6 1 0 1 6 1 4 4 6 1 0 6 6 1 4 7 6 1 0 0 7 1 0 1 7 1 0 3 7 1 0 6 7 1 0 7 7 1 0 \"\""

#define LEVEL_26 "SquareCells 1 10 10 0 0 2 2 1 1 2 2 0 0 0 0 0 0 0 0 0 0 2 2 0 0 1 20 2 0 1 0 3 0 1 12 4 0 1 0 5 0 1 0 6 0 1 12 7 0 1 0 9 0 1 20 0 1 1 0 1 1 1 0 3 1 1 0 4 1 1 0 5 1 1 0 6 1 1 0 8 1 1 0 9 1 1 0 1 2 1 0 2 2 1 0 4 2 1 0 5 2 1 0 7 2 1 0 8 2 1 0 0 3 1 1 2 3 1 0 3 3 1 0 6 3 1 0 7 3 1 0 9 3 1 1 1 4 1 0 3 4 1 20 4 4 1 0 5 4 1 0 6 4 1 20 8 4 1 0 0 5 1 5 1 5 1 0 2 5 1 0 4 5 1 0 5 5 1 0 7 5 1 0 8 5 1 0 9 5 1 5 1 6 1 0 3 6 1 20 6 6 1 20 8 6 1 0 0 7 1 1 2 7 1 0 3 7 1 0 6 7 1 0 7 7 1 0 9 7 1 1 2 8 1 0 3 8 1 0 4 8 1 0 5 8 1 0 6 8 1 0 7 8 1 0 0 9 1 20 1 9 1 0 2 9 1 0 4 9 1 0 5 9 1 0 7 9 1 0 8 9 1 0 9 9 1 20 \"\""

#define LEVEL_27 "SquareCells 1 12 12 0 1 1 1 2 1 1 2 1 1 1 0 1 2 2 1 0 1 1 1 0 1 2 1 6 0 1 0 7 0 1 0 1 1 1 0 2 1 1 5 3 1 1 0 4 1 1 0 8 1 1 0 9 1 1 0 10 1 1 0 11 1 1 5 1 2 1 0 5 2 1 0 8 2 1 5 3 3 1 5 5 3 1 0 6 3 1 5 7 3 1 0 0 4 1 5 1 4 1 0 2 4 1 0 3 4 1 0 5 4 1 0 8 4 1 0 9 4 1 0 10 4 1 5 11 4 1 0 7 5 1 5 11 5 1 0 2 6 1 5 5 6 1 0 7 6 1 0 8 6 1 0 9 6 1 0 0 7 1 0 1 7 1 0 2 7 1 0 4 7 1 5 5 7 1 0 7 7 1 0 0 8 1 0 4 8 1 0 5 8 1 5 8 8 1 0 9 8 1 5 10 8 1 0 2 9 1 0 7 9 1 0 8 9 1 0 1 10 1 5 2 10 1 0 9 10 1 0 10 10 1 0 11 10 1 5 1 11 1 0 2 11 1 0 4 11 1 0 5 11 1 0 6 11 1 0 7 11 1 5 8 11 1 0 10 11 1 0 11 11 1 0 \"\""

#define LEVEL_28 "SquareCells 1 4 4 2 1 1 1 2 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 0 1 1 0 1 1 1 0 3 2 1 0 0 3 1 0 3 3 1 0 \"\""

#define LEVEL_29 "SquareCells 1 12 12 1 0 0 1 1 1 1 1 1 2 0 1 0 2 0 1 1 0 0 1 1 0 0 0 0 0 1 16 1 0 1 0 2 0 1 0 3 0 1 16 4 0 1 0 5 0 1 0 6 0 1 0 7 0 1 0 8 0 1 16 10 0 1 0 11 0 1 0 0 1 1 0 1 1 1 0 4 1 1 0 7 1 1 0 9 1 1 0 11 1 1 0 0 2 1 0 2 2 1 2 4 2 1 0 7 2 1 0 9 2 1 2 11 2 1 4 2 3 1 0 5 3 1 0 6 3 1 0 0 4 1 1 4 4 1 0 7 4 1 0 10 4 1 4 11 4 1 0 3 5 1 0 5 5 1 0 6 5 1 0 8 5 1 0 10 5 1 0 3 6 1 0 5 6 1 0 6 6 1 4 8 6 1 0 10 6 1 0 0 7 1 1 4 7 1 0 7 7 1 0 11 7 1 0 1 8 1 2 2 8 1 0 5 8 1 0 6 8 1 0 9 8 1 0 10 8 1 4 11 8 1 0 3 9 1 0 4 9 1 0 7 9 1 0 8 9 1 0 0 10 1 0 2 10 1 2 4 10 1 12 5 10 1 0 6 10 1 0 7 10 1 12 9 10 1 0 10 10 1 0 11 10 1 0 0 11 1 2 2 11 1 0 4 11 1 0 5 11 1 0 6 11 1 0 7 11 1 0 9 11 1 0 10 11 1 0 11 11 1 6 \"\""

#define LEVEL_30 "SquareCells 1 8 8 1 2 1 1 1 1 0 2 1 2 2 1 1 1 2 1 2 0 1 0 4 0 1 0 5 0 1 0 7 0 1 4 0 1 1 0 1 1 1 0 2 1 1 0 3 1 1 18 7 1 1 0 3 2 1 0 4 2 1 0 5 2 1 0 7 2 1 0 0 3 1 0 1 3 1 18 2 3 1 0 3 3 1 0 7 3 1 0 1 4 1 0 5 4 1 0 1 5 1 0 3 5 1 0 4 5 1 9 5 5 1 0 6 5 1 0 7 5 1 0 0 6 1 0 1 6 1 0 2 6 1 0 4 6 1 0 7 6 1 0 0 7 1 18 4 7 1 0 \"\""

#define LEVEL_31 "SquareCells 1 14 14 0 0 0 0 2 2 2 2 2 2 2 2 2 2 0 2 0 2 0 2 1 1 1 2 1 2 0 1 0 0 1 0 1 0 1 0 3 0 1 0 4 0 1 0 7 0 1 0 8 0 1 0 9 0 1 0 10 0 1 4 12 0 1 0 13 0 1 3 0 1 1 0 1 1 1 5 3 1 1 3 13 1 1 0 0 2 1 0 2 2 1 1 4 2 1 0 5 2 1 0 6 2 1 0 7 2 1 0 8 2 1 16 11 2 1 1 1 3 1 2 3 3 1 0 4 3 1 0 5 3 1 0 6 3 1 0 7 3 1 0 8 3 1 0 10 3 1 0 12 3 1 5 13 3 1 0 1 4 1 0 3 4 1 16 4 4 1 0 5 4 1 0 6 4 1 16 7 4 1 0 10 4 1 2 12 4 1 0 13 4 1 0 0 5 1 2 2 5 1 0 12 5 1 0 0 6 1 0 2 6 1 0 2 6 1 0 3 6 1 0 4 6 1 0 5 6 1 0 6 6 1 0 7 6 1 0 8 6 1 0 9 6 1 0 10 6 1 0 11 6 1 0 13 6 1 0 1 7 1 2 4 7 1 0 6 7 1 0 7 7 1 0 1 8 1 0 3 8 1 0 5 8 1 0 8 8 1 0 9 8 1 0 10 8 1 0 11 8 1 5 0 9 1 2 3 9 1 2 5 9 1 3 6 9 1 0 10 9 1 0 12 9 1 0 13 9 1 0 0 10 1 0 7 10 1 0 12 10 1 0 13 10 1 0 2 11 1 1 5 11 1 0 7 11 1 0 8 11 1 4 9 11 1 0 11 11 1 1 13 11 1 0 1 12 1 3 3 12 1 0 5 12 1 2 10 12 1 7 12 12 1 7 13 12 1 0 0 13 1 0 1 13 1 0 3 13 1 3 4 13 1 0 6 13 1 0 7 13 1 0 8 13 1 0 9 13 1 0 10 13 1 0 11 13 1 0 \"\""

#define LEVEL_32 "SquareCells 1 12 12 0 2 1 0 0 2 1 2 0 1 1 1 1 1 1 0 1 2 1 1 1 2 2 1 1 0 1 14 2 0 1 0 5 0 1 14 6 0 1 0 10 0 1 0 11 0 1 3 1 1 1 0 2 1 1 0 5 1 1 0 6 1 1 0 8 1 1 0 11 1 1 0 1 2 1 0 2 2 1 0 3 2 1 0 4 2 1 0 5 2 1 0 6 2 1 0 8 2 1 6 9 2 1 0 8 3 1 0 9 3 1 0 10 3 1 0 0 4 1 0 1 4 1 0 2 4 1 0 3 4 1 4 6 4 1 0 7 4 1 0 4 5 1 12 5 5 1 0 6 5 1 0 7 5 1 0 9 5 1 0 10 5 1 0 11 5 1 0 1 6 1 0 4 6 1 0 5 6 1 0 6 6 1 0 7 6 1 0 9 6 1 4 1 7 1 0 6 7 1 0 7 7 1 0 10 7 1 0 11 7 1 0 0 8 1 0 1 8 1 0 2 8 1 5 4 8 1 1 10 8 1 3 5 9 1 0 6 9 1 0 8 9 1 0 0 10 1 2 2 10 1 2 4 10 1 6 5 10 1 0 7 10 1 3 8 10 1 0 10 10 1 4 11 10 1 0 0 11 1 0 2 11 1 0 5 11 1 0 6 11 1 0 10 11 1 0 11 11 1 0 \"\""

#define LEVEL_33 "SquareCells 1 4 4 0 2 1 2 0 1 1 1 0 0 1 0 1 0 1 0 2 0 1 0 3 0 1 0 1 1 1 0 2 2 1 0 1 3 1 0 3 3 1 0 \"\""

#define LEVEL_34 "SquareCells 1 12 12 0 1 0 0 2 0 0 1 2 0 1 1 0 1 0 0 0 0 0 1 2 1 0 1 0 0 1 1 3 0 1 1 6 0 1 1 9 0 1 1 11 1 1 0 1 2 1 0 2 2 1 2 4 2 1 0 5 2 1 2 7 2 1 0 8 2 1 2 11 2 1 2 0 3 1 1 3 3 1 0 10 3 1 0 3 4 1 0 4 4 1 3 7 4 1 3 8 4 1 0 10 4 1 3 11 4 1 0 1 5 1 0 2 5 1 2 5 5 1 0 7 5 1 0 9 5 1 0 0 6 1 1 3 6 1 0 5 6 1 0 6 6 1 4 9 6 1 4 10 6 1 0 11 6 1 0 3 7 1 0 4 7 1 3 6 7 1 0 8 7 1 0 1 8 1 0 2 8 1 2 5 8 1 0 8 8 1 5 9 8 1 0 10 8 1 0 0 9 1 1 3 9 1 0 5 9 1 0 6 9 1 3 8 9 1 0 11 9 1 0 3 10 1 0 4 10 1 3 9 10 1 0 10 10 1 6 11 10 1 0 1 11 1 0 2 11 1 2 5 11 1 0 6 11 1 0 7 11 1 0 8 11 1 4 10 11 1 0 11 11 1 0 \"\""

#define LEVEL_35 "SquareCells 1 12 12 1 2 2 2 2 2 2 0 2 0 0 1 1 1 2 1 2 1 0 1 2 2 1 1 0 0 1 0 3 0 1 0 4 0 1 0 5 0 1 0 6 0 1 0 7 0 1 0 8 0 1 0 9 0 1 0 11 0 1 0 1 1 1 0 2 1 1 0 1 2 1 3 3 2 1 3 5 2 1 3 6 2 1 0 7 2 1 3 0 3 1 0 2 3 1 0 3 3 1 0 9 3 1 0 10 3 1 0 11 3 1 0 0 4 1 2 4 4 1 2 5 4 1 0 7 4 1 2 8 4 1 0 11 5 1 0 0 6 1 0 1 6 1 4 2 6 1 0 4 6 1 0 5 6 1 4 6 6 1 0 7 6 1 0 9 6 1 4 10 6 1 0 11 6 1 0 0 7 1 0 2 8 1 0 3 8 1 2 7 8 1 2 10 8 1 2 7 9 1 0 10 9 1 0 0 10 1 0 1 10 1 0 4 10 1 0 5 10 1 0 8 10 1 0 9 10 1 0 2 11 1 0 3 11 1 0 6 11 1 0 7 11 1 0 10 11 1 0 11 11 1 0 \"\""

#define LEVEL_36 "SquareCells 1 12 12 1 1 1 0 1 0 1 1 1 1 1 1 2 1 0 1 2 1 1 1 2 0 1 2 0 0 1 0 1 0 1 4 2 0 1 0 4 0 1 4 5 0 1 0 6 0 1 0 8 0 1 0 9 0 1 0 10 0 1 4 1 1 1 0 5 1 1 0 9 1 1 0 0 3 1 0 1 3 1 0 2 3 1 0 4 3 1 0 6 3 1 0 11 3 1 0 0 4 1 0 4 4 1 0 6 4 1 0 7 4 1 0 11 4 1 0 0 5 1 0 1 5 1 9 4 5 1 6 6 5 1 7 8 5 1 0 11 5 1 7 0 6 1 0 4 6 1 0 6 6 1 0 9 6 1 1 11 6 1 0 0 7 1 0 4 7 1 0 6 7 1 0 10 7 1 0 11 7 1 0 0 8 1 0 4 8 1 0 6 8 1 0 11 8 1 0 3 10 1 0 7 10 1 0 11 10 1 0 0 11 1 1 2 11 1 0 3 11 1 4 4 11 1 0 6 11 1 0 7 11 1 0 8 11 1 4 10 11 1 3 11 11 1 0 \"Original game by\nMatthew Brown\""

void LevelLoad(char* pstr, int nLevelNum);

#endif

