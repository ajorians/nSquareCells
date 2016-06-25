#ifndef GAME_H
#define GAME_H

#include <SquareLib/SquareLib.h>
#include <ngc.h>
#include "Background.h"
#include "StarDrawer.h"

struct Metrics;
struct Piece;
struct Selector;
struct Indicators;

struct Game
{
   SquareLib m_Square;
   int m_bWon;
   struct Metrics* m_pMetrics;
   struct Piece* m_apPieces;
   struct Selector* m_pSelector;
   struct Indicators* m_pIndicators;
   int m_bShouldQuit;
   Gc m_gc;
   struct Background* m_pBackground;
   struct StarDrawer* m_pStarDrawer;
};

void CreateGame(struct Game** ppGame, const char* pstrLevelData);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
int GameShouldQuit(struct Game* pMenu);

#endif
