#ifndef HELP_H
#define HELP_H

#include "Background.h"

struct Help
{
   struct Background* m_pBackground;
   //struct Config* m_pConfig;//Does not own
};

void CreateHelp(struct Help** ppHelp, struct Config* pConfig);
void FreeHelp(struct Help** ppHelp);
int HelpLoop(struct Help* pHelp);

#endif
