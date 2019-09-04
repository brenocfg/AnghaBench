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
struct TYPE_3__ {size_t pos; size_t size; void* dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  ZBUFF_CCtx ;

/* Variables and functions */
 size_t ZSTD_flushStream (int /*<<< orphan*/ *,TYPE_1__*) ; 

size_t ZBUFF_compressFlush(ZBUFF_CCtx* zbc, void* dst, size_t* dstCapacityPtr)
{
    size_t result;
    ZSTD_outBuffer outBuff;
    outBuff.dst = dst;
    outBuff.pos = 0;
    outBuff.size = *dstCapacityPtr;
    result = ZSTD_flushStream(zbc, &outBuff);
    *dstCapacityPtr = outBuff.pos;
    return result;
}