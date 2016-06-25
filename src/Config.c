#include <os.h>
#include "Config.h"

void CreateConfig(struct Config** ppConfig)
{
   *ppConfig = malloc(sizeof(struct Config));

   struct Config* pConfig = *ppConfig;
   for(int nLevel = 0; nLevel<36; nLevel++)
      pConfig->m_Stars[nLevel] = 0;

   pConfig->m_Archive = NULL;
   ArchiveCreate(&pConfig->m_Archive);

   OpenArchiveFile(pConfig->m_Archive, "SquareCellSettings.tns");
   int nSettings = GetNumberArchives(pConfig->m_Archive, "Settings");
   char strName[MAX_NAME_LENGTH];
   for(int i=0; i<nSettings; i++) {
      strcpy(strName, GetName(pConfig->m_Archive, "Settings", i));

      for(int nLevel = 0; nLevel<36; nLevel++) {
         char buffer[8];
         sprintf(buffer, "Level%d", nLevel);

         if( strcmp(strName, buffer) == 0 ) {
            pConfig->m_Stars[nLevel] = atoi( GetValue(pConfig->m_Archive, "Settings", i) );
            break;
         }
      }
   }
}

void FreeConfig(struct Config** ppConfig)
{
   struct Config* pConfig = *ppConfig;
   ArchiveSetBatchMode(pConfig->m_Archive, ARCHIVE_ENABLE_BATCH);
   for(int nLevel=0; nLevel<36; nLevel++) {
      char buffer[8];
      sprintf(buffer, "%d", pConfig->m_Stars[nLevel]);
      char bufferName[8];
      sprintf(bufferName, "Level%d", nLevel);
      UpdateArchiveEntry(pConfig->m_Archive, "Settings", bufferName, buffer, NULL);
   }
   ArchiveSetBatchMode(pConfig->m_Archive, ARCHIVE_DISABLE_BATCH);

   ArchiveFree(&pConfig->m_Archive);

   free(*ppConfig);
   *ppConfig = NULL;
}

void SetBeatLevel(struct Config* pConfig, int nLevelNum, int nStars)
{
   printf("Config: Level: %d Stars: %d\n", nLevelNum, nStars);
   if( nLevelNum < 0 || nLevelNum >= 36 )
      return;

   if( nStars <= pConfig->m_Stars[nLevelNum] )
      return;

   pConfig->m_Stars[nLevelNum] = nStars; 
}

void GetBeatLevel(struct Config* pConfig, int nLevelNum, int* pnStars)
{
   if( pnStars ) {
      *pnStars = 0;

      if( nLevelNum >= 0 && nLevelNum <36 )
         *pnStars = pConfig->m_Stars[nLevelNum];
   }
}

