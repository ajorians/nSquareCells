#ifndef GAME_H
#define GAME_H

#include <SquareLib/SquareLib.h>
#include <ngc.h>
#include "Background.h"

struct Metrics;
struct Piece;
struct Selector;
struct Indicators;

struct Game
{
   SquareLib m_Square;
   struct Metrics* m_pMetrics;
   struct Piece* m_apPieces;
   struct Selector* m_pSelector;
   struct Indicators* m_pIndicators;
   int m_bShouldQuit;
   Gc m_gc;
   int m_R, m_G, m_B;
   struct Background* m_pBackground;
};

void CreateGame(struct Game** ppGame, const char* pstrLevelData);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
int GameShouldQuit(struct Game* pMenu);

#endif
