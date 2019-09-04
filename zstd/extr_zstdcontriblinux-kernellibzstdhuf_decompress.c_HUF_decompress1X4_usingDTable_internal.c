#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tableLog; } ;
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  HUF_DEltX4 ;
typedef  TYPE_1__ DTableDesc ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BIT_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BIT_initDStream (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUF_decodeStreamX4 (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
 TYPE_1__ HUF_getDTableDesc (int /*<<< orphan*/  const*) ; 
 scalar_t__ HUF_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 

__attribute__((used)) static size_t HUF_decompress1X4_usingDTable_internal(void *dst, size_t dstSize, const void *cSrc, size_t cSrcSize, const HUF_DTable *DTable)
{
	BIT_DStream_t bitD;

	/* Init */
	{
		size_t const errorCode = BIT_initDStream(&bitD, cSrc, cSrcSize);
		if (HUF_isError(errorCode))
			return errorCode;
	}

	/* decode */
	{
		BYTE *const ostart = (BYTE *)dst;
		BYTE *const oend = ostart + dstSize;
		const void *const dtPtr = DTable + 1; /* force compiler to not use strict-aliasing */
		const HUF_DEltX4 *const dt = (const HUF_DEltX4 *)dtPtr;
		DTableDesc const dtd = HUF_getDTableDesc(DTable);
		HUF_decodeStreamX4(ostart, &bitD, oend, dt, dtd.tableLog);
	}

	/* check */
	if (!BIT_endOfDStream(&bitD))
		return ERROR(corruption_detected);

	/* decoded size */
	return dstSize;
}