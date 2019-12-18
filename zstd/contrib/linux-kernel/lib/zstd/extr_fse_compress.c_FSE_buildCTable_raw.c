#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_2__ {unsigned int deltaNbBits; unsigned int deltaFindState; } ;
typedef  TYPE_1__ FSE_symbolCompressionTransform ;
typedef  int /*<<< orphan*/  FSE_CTable ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 

size_t FSE_buildCTable_raw(FSE_CTable *ct, unsigned nbBits)
{
	const unsigned tableSize = 1 << nbBits;
	const unsigned tableMask = tableSize - 1;
	const unsigned maxSymbolValue = tableMask;
	void *const ptr = ct;
	U16 *const tableU16 = ((U16 *)ptr) + 2;
	void *const FSCT = ((U32 *)ptr) + 1 /* header */ + (tableSize >> 1); /* assumption : tableLog >= 1 */
	FSE_symbolCompressionTransform *const symbolTT = (FSE_symbolCompressionTransform *)(FSCT);
	unsigned s;

	/* Sanity checks */
	if (nbBits < 1)
		return ERROR(GENERIC); /* min size */

	/* header */
	tableU16[-2] = (U16)nbBits;
	tableU16[-1] = (U16)maxSymbolValue;

	/* Build table */
	for (s = 0; s < tableSize; s++)
		tableU16[s] = (U16)(tableSize + s);

	/* Build Symbol Transformation Table */
	{
		const U32 deltaNbBits = (nbBits << 16) - (1 << nbBits);
		for (s = 0; s <= maxSymbolValue; s++) {
			symbolTT[s].deltaNbBits = deltaNbBits;
			symbolTT[s].deltaFindState = s - 1;
		}
	}

	return 0;
}