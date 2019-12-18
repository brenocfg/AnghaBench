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
typedef  int /*<<< orphan*/  HUF_CElt ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BIT_CStream_t ;

/* Variables and functions */
 size_t BIT_closeCStream (int /*<<< orphan*/ *) ; 
 size_t BIT_initCStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HUF_FLUSHBITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_FLUSHBITS_1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_FLUSHBITS_2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_encodeSymbol (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const*) ; 
 scalar_t__ HUF_isError (size_t const) ; 

size_t HUF_compress1X_usingCTable(void *dst, size_t dstSize, const void *src, size_t srcSize, const HUF_CElt *CTable)
{
	const BYTE *ip = (const BYTE *)src;
	BYTE *const ostart = (BYTE *)dst;
	BYTE *const oend = ostart + dstSize;
	BYTE *op = ostart;
	size_t n;
	BIT_CStream_t bitC;

	/* init */
	if (dstSize < 8)
		return 0; /* not enough space to compress */
	{
		size_t const initErr = BIT_initCStream(&bitC, op, oend - op);
		if (HUF_isError(initErr))
			return 0;
	}

	n = srcSize & ~3; /* join to mod 4 */
	switch (srcSize & 3) {
	case 3: HUF_encodeSymbol(&bitC, ip[n + 2], CTable); HUF_FLUSHBITS_2(&bitC);
	case 2: HUF_encodeSymbol(&bitC, ip[n + 1], CTable); HUF_FLUSHBITS_1(&bitC);
	case 1: HUF_encodeSymbol(&bitC, ip[n + 0], CTable); HUF_FLUSHBITS(&bitC);
	case 0:
	default:;
	}

	for (; n > 0; n -= 4) { /* note : n&3==0 at this stage */
		HUF_encodeSymbol(&bitC, ip[n - 1], CTable);
		HUF_FLUSHBITS_1(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 2], CTable);
		HUF_FLUSHBITS_2(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 3], CTable);
		HUF_FLUSHBITS_1(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 4], CTable);
		HUF_FLUSHBITS(&bitC);
	}

	return BIT_closeCStream(&bitC);
}