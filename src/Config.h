#ifndef CONFIG_H
#define CONFIG_H

#include "ArchiveLib/ArchiveLib.h"

struct Config
{
   ArchiveLib m_Archive;
   int m_Stars[36];
};

void CreateConfig(struct Config** ppConfig);
void FreeConfig(struct Config** ppConfig);
void SetBeatLevel(struct Config* pConfig, int nLevelNum, int nStars);
void GetBeatLevel(struct Config* pConfig, int nLevelNum, int* pnStars);

#endif

