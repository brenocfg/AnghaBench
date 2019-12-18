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
typedef  int U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_writeLE16 (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_writeLE32 (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  set_rle ; 

__attribute__((used)) static size_t ZSTD_compressRleLiteralsBlock(void *dst, size_t dstCapacity, const void *src, size_t srcSize)
{
	BYTE *const ostart = (BYTE * const)dst;
	U32 const flSize = 1 + (srcSize > 31) + (srcSize > 4095);

	(void)dstCapacity; /* dstCapacity already guaranteed to be >=4, hence large enough */

	switch (flSize) {
	case 1: /* 2 - 1 - 5 */ ostart[0] = (BYTE)((U32)set_rle + (srcSize << 3)); break;
	case 2: /* 2 - 2 - 12 */ ZSTD_writeLE16(ostart, (U16)((U32)set_rle + (1 << 2) + (srcSize << 4))); break;
	default: /*note : should not be necessary : flSize is necessarily within {1,2,3} */
	case 3: /* 2 - 2 - 20 */ ZSTD_writeLE32(ostart, (U32)((U32)set_rle + (3 << 2) + (srcSize << 4))); break;
	}

	ostart[flSize] = *(const BYTE *)src;
	return flSize + 1;
}