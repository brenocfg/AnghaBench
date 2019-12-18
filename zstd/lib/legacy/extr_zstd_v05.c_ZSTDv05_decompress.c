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
typedef  int /*<<< orphan*/  ZSTDv05_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTDv05_createDCtx () ; 
 size_t ZSTDv05_decompressDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTDv05_freeDCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTDv05_decompress(void* dst, size_t maxDstSize, const void* src, size_t srcSize)
{
#if defined(ZSTDv05_HEAPMODE) && (ZSTDv05_HEAPMODE==1)
    size_t regenSize;
    ZSTDv05_DCtx* dctx = ZSTDv05_createDCtx();
    if (dctx==NULL) return ERROR(memory_allocation);
    regenSize = ZSTDv05_decompressDCtx(dctx, dst, maxDstSize, src, srcSize);
    ZSTDv05_freeDCtx(dctx);
    return regenSize;
#else
    ZSTDv05_DCtx dctx;
    return ZSTDv05_decompressDCtx(&dctx, dst, maxDstSize, src, srcSize);
#endif
}