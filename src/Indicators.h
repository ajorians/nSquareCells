#ifndef INDICATORS_H
#define INDICATORS_H

#include <ngc.h>
#include <SquareLib/SquareLib.h>

struct Metrics;

struct Indicators
{
   SquareLib m_Square;//Does not own
   struct Metrics* m_pMetrics;//Does not own
};

void CreateIndicators(struct Indicators** ppIndicators, SquareLib square, struct Metrics* pMetrics);
void FreeIndicators(struct Indicators** ppIndicators);
void IndicatorsDraw(struct Indicators* pIndicators, Gc* pgc);

#endif

