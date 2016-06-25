#ifndef MAINMENU_H
#define MAINMENU_H

#include "Background.h"
#include "Config.h"

//#define SHOW_LEVEL_DIMENSIONS

enum MenuChoice
{
   Play,
   Options,
   Help,
   Quit
};

struct MainMenu
{
   enum MenuChoice m_eChoice;
   int m_nLevelNum;
   struct Background* m_pBackground;
   struct Config* m_pConfig;//Does not own
};

void CreateMainMenu(struct MainMenu** ppMenu, int nLevelNum, struct Config* pConfig);
void FreeMainMenu(struct MainMenu** ppMenu);
int MainMenuLoop(struct MainMenu* pMenu);
int MainMenuShouldQuit(struct MainMenu* pMenu);
int MainMenuGetLevelNum(struct MainMenu* pMenu);

#endif
