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
typedef  unsigned int U32 ;
typedef  int /*<<< orphan*/  HUFv05_DEltX4 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv05_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITv05_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BITv05_initDStream (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv05_decodeStreamX4 (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,unsigned int const) ; 
 scalar_t__ HUFv05_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 

size_t HUFv05_decompress1X4_usingDTable(
          void* dst,  size_t dstSize,
    const void* cSrc, size_t cSrcSize,
    const unsigned* DTable)
{
    const BYTE* const istart = (const BYTE*) cSrc;
    BYTE* const ostart = (BYTE*) dst;
    BYTE* const oend = ostart + dstSize;

    const U32 dtLog = DTable[0];
    const void* const dtPtr = DTable;
    const HUFv05_DEltX4* const dt = ((const HUFv05_DEltX4*)dtPtr) +1;
    size_t errorCode;

    /* Init */
    BITv05_DStream_t bitD;
    errorCode = BITv05_initDStream(&bitD, istart, cSrcSize);
    if (HUFv05_isError(errorCode)) return errorCode;

    /* finish bitStreams one by one */
    HUFv05_decodeStreamX4(ostart, &bitD, oend,     dt, dtLog);

    /* check */
    if (!BITv05_endOfDStream(&bitD)) return ERROR(corruption_detected);

    /* decoded size */
    return dstSize;
}