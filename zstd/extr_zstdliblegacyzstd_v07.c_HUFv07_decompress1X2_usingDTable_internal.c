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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int /*<<< orphan*/  tableLog; } ;
typedef  int /*<<< orphan*/  HUFv07_DTable ;
typedef  int /*<<< orphan*/  HUFv07_DEltX2 ;
typedef  TYPE_1__ DTableDesc ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv07_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITv07_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BITv07_initDStream (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv07_decodeStreamX2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 
 TYPE_1__ HUFv07_getDTableDesc (int /*<<< orphan*/  const*) ; 
 scalar_t__ HUFv07_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 

__attribute__((used)) static size_t HUFv07_decompress1X2_usingDTable_internal(
          void* dst,  size_t dstSize,
    const void* cSrc, size_t cSrcSize,
    const HUFv07_DTable* DTable)
{
    BYTE* op = (BYTE*)dst;
    BYTE* const oend = op + dstSize;
    const void* dtPtr = DTable + 1;
    const HUFv07_DEltX2* const dt = (const HUFv07_DEltX2*)dtPtr;
    BITv07_DStream_t bitD;
    DTableDesc const dtd = HUFv07_getDTableDesc(DTable);
    U32 const dtLog = dtd.tableLog;

    { size_t const errorCode = BITv07_initDStream(&bitD, cSrc, cSrcSize);
      if (HUFv07_isError(errorCode)) return errorCode; }

    HUFv07_decodeStreamX2(op, &bitD, oend, dt, dtLog);

    /* check */
    if (!BITv07_endOfDStream(&bitD)) return ERROR(corruption_detected);

    return dstSize;
}