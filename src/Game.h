#ifndef GAME_H
#define GAME_H

#include <SquareLib/SquareLib.h>

struct Game
{
   SquareLib m_Square;
   int m_nSelectionX, m_nSelectionY;
   int m_bShouldQuit;
};

void CreateGame(struct Game** ppGame, const char* pstrLevelData);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
int GameShouldQuit(struct Game* pMenu);

#endif
