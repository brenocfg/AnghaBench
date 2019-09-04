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
typedef  int /*<<< orphan*/  ZSTDv06_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv06_checkContinuity (int /*<<< orphan*/ *,void*) ; 
 size_t ZSTDv06_decompressBlock_internal (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

size_t ZSTDv06_decompressBlock(ZSTDv06_DCtx* dctx,
                            void* dst, size_t dstCapacity,
                      const void* src, size_t srcSize)
{
    ZSTDv06_checkContinuity(dctx, dst);
    return ZSTDv06_decompressBlock_internal(dctx, dst, dstCapacity, src, srcSize);
}