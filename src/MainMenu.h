#ifndef MAINMENU_H
#define MAINMENU_H

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
};

void CreateMainMenu(struct MainMenu** ppMenu);
void FreeMainMenu(struct MainMenu** ppMenu);
int MainMenuLoop(struct MainMenu* pMenu);
int MainMenuShouldQuit(struct MainMenu* pMenu);

#endif
