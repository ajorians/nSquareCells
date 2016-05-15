#include "Levels.h"
#include <string.h>

void LevelLoad(char* pstr, int nLevelNum)
{
   switch( nLevelNum ) {
   case 1: strcpy(pstr, LEVEL_1); break;
   case 2: strcpy(pstr, LEVEL_2); break;
   case 3: strcpy(pstr, LEVEL_3); break;
   case 4: strcpy(pstr, LEVEL_4); break;
   case 5: strcpy(pstr, LEVEL_5); break;
   case 6: strcpy(pstr, LEVEL_6); break;
   case 7: strcpy(pstr, LEVEL_7); break;
   case 19: strcpy(pstr, LEVEL_19); break;
   default: strcpy(pstr, LEVEL_33); break;
   }
}

