#ifndef METRICS_H
#define METRICS_H

#include <SquareLib/SquareLib.h>

struct Metrics
{
   SquareLib m_Square;//Does not own
   int m_nPieceDim;
   int m_nMaxColIndicators;
   int m_nMaxRowIndicators;
   int m_nLeft;
   int m_nTop;
   int m_nLeftBoard;
   int m_nTopBoard;
};

void CreateMetrics(struct Metrics** ppMetrics, SquareLib square);
void FreeMetrics(struct Metrics** ppMetrics);
int MetricsGetPieceDim(struct Metrics* pMetrics);
int MetricsGetMaxColIndicators(struct Metrics* pMetrics);
int MetricsGetMaxRowIndicators(struct Metrics* pMetrics);
int MetricsGetLeft(struct Metrics* pMetrics);
int MetricsGetTop(struct Metrics* pMetrics);
int MetricsGetLeftBoard(struct Metrics* pMetrics);
int MetricsGetTopBoard(struct Metrics* pMetrics);
int MetricsGetXForSpot(struct Metrics* pMetrics, int nX, int nY);
int MetricsGetYForSpot(struct Metrics* pMetrics, int nX, int nY);

#endif

