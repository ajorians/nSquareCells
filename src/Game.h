#ifndef GAME_H
#define GAME_H

#include <SquareLib/SquareLib.h>

struct Game
{
   SquareLib m_Square;
};

void CreateGame(struct Game** ppGame);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
//int GameShouldQuit(struct Game* pMenu);

#endif
