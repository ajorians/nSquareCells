#ifndef GAME_H
#define GAME_H

#include <SquareLib/SquareLib.h>

struct Metrics;
struct Piece;
struct Selector;

struct Game
{
   SquareLib m_Square;
   struct Metrics* m_pMetrics;
   struct Piece* m_apPieces;
   struct Selector* m_pSelector;
   int m_bShouldQuit;
};

void CreateGame(struct Game** ppGame, const char* pstrLevelData);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
int GameShouldQuit(struct Game* pMenu);

#endif
