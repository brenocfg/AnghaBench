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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  HUFv06_DEltX2 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv06_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITv06_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BITv06_initDStream (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv06_decodeStreamX2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 
 scalar_t__ HUFv06_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 

size_t HUFv06_decompress1X2_usingDTable(
          void* dst,  size_t dstSize,
    const void* cSrc, size_t cSrcSize,
    const U16* DTable)
{
    BYTE* op = (BYTE*)dst;
    BYTE* const oend = op + dstSize;
    const U32 dtLog = DTable[0];
    const void* dtPtr = DTable;
    const HUFv06_DEltX2* const dt = ((const HUFv06_DEltX2*)dtPtr)+1;
    BITv06_DStream_t bitD;

    { size_t const errorCode = BITv06_initDStream(&bitD, cSrc, cSrcSize);
      if (HUFv06_isError(errorCode)) return errorCode; }

    HUFv06_decodeStreamX2(op, &bitD, oend, dt, dtLog);

    /* check */
    if (!BITv06_endOfDStream(&bitD)) return ERROR(corruption_detected);

    return dstSize;
}