#ifndef OPTIONS_H
#define OPTIONS_H

#include "Background.h"
#include "Config.h"

struct Options
{
   struct Background* m_pBackground;
   struct Config* m_pConfig;//Does not own
};

void CreateOptions(struct Options** ppOptions, struct Config* pConfig);
void FreeOptions(struct Options** ppOptions);
int OptionsLoop(struct Options* pOptions);

#endif
