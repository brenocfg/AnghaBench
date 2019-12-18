#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U64 ;
typedef  size_t U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int div_u64 (int const,size_t) ; 

__attribute__((used)) static size_t FSE_normalizeM2(short *norm, U32 tableLog, const unsigned *count, size_t total, U32 maxSymbolValue)
{
	short const NOT_YET_ASSIGNED = -2;
	U32 s;
	U32 distributed = 0;
	U32 ToDistribute;

	/* Init */
	U32 const lowThreshold = (U32)(total >> tableLog);
	U32 lowOne = (U32)((total * 3) >> (tableLog + 1));

	for (s = 0; s <= maxSymbolValue; s++) {
		if (count[s] == 0) {
			norm[s] = 0;
			continue;
		}
		if (count[s] <= lowThreshold) {
			norm[s] = -1;
			distributed++;
			total -= count[s];
			continue;
		}
		if (count[s] <= lowOne) {
			norm[s] = 1;
			distributed++;
			total -= count[s];
			continue;
		}

		norm[s] = NOT_YET_ASSIGNED;
	}
	ToDistribute = (1 << tableLog) - distributed;

	if ((total / ToDistribute) > lowOne) {
		/* risk of rounding to zero */
		lowOne = (U32)((total * 3) / (ToDistribute * 2));
		for (s = 0; s <= maxSymbolValue; s++) {
			if ((norm[s] == NOT_YET_ASSIGNED) && (count[s] <= lowOne)) {
				norm[s] = 1;
				distributed++;
				total -= count[s];
				continue;
			}
		}
		ToDistribute = (1 << tableLog) - distributed;
	}

	if (distributed == maxSymbolValue + 1) {
		/* all values are pretty poor;
		   probably incompressible data (should have already been detected);
		   find max, then give all remaining points to max */
		U32 maxV = 0, maxC = 0;
		for (s = 0; s <= maxSymbolValue; s++)
			if (count[s] > maxC)
				maxV = s, maxC = count[s];
		norm[maxV] += (short)ToDistribute;
		return 0;
	}

	if (total == 0) {
		/* all of the symbols were low enough for the lowOne or lowThreshold */
		for (s = 0; ToDistribute > 0; s = (s + 1) % (maxSymbolValue + 1))
			if (norm[s] > 0)
				ToDistribute--, norm[s]++;
		return 0;
	}

	{
		U64 const vStepLog = 62 - tableLog;
		U64 const mid = (1ULL << (vStepLog - 1)) - 1;
		U64 const rStep = div_u64((((U64)1 << vStepLog) * ToDistribute) + mid, (U32)total); /* scale on remaining */
		U64 tmpTotal = mid;
		for (s = 0; s <= maxSymbolValue; s++) {
			if (norm[s] == NOT_YET_ASSIGNED) {
				U64 const end = tmpTotal + (count[s] * rStep);
				U32 const sStart = (U32)(tmpTotal >> vStepLog);
				U32 const sEnd = (U32)(end >> vStepLog);
				U32 const weight = sEnd - sStart;
				if (weight < 1)
					return ERROR(GENERIC);
				norm[s] = (short)weight;
				tmpTotal = end;
			}
		}
	}

	return 0;
}