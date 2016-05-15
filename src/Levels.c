#include "Levels.h"
#include <string.h>

void LevelLoad(char* pstr, int nLevelNum)
{
   if( nLevelNum == 1 ) {
      strcpy(pstr, LEVEL_1);
   }
   else if( nLevelNum == 2 ) {
      strcpy(pstr, LEVEL_2);
   }
   else if( nLevelNum == 3 ) {
      strcpy(pstr, LEVEL_3);
   }
   else if( nLevelNum == 4 ) {
      strcpy(pstr, LEVEL_4);
   }
   else if( nLevelNum == 5 ) {
      strcpy(pstr, LEVEL_5);
   }
   else if( nLevelNum == 6 ) {
      strcpy(pstr, LEVEL_6);
   }
   else if( nLevelNum == 19 ) {
      strcpy(pstr, LEVEL_19);
   }
   else {
      strcpy(pstr, LEVEL_33);
   }
}

