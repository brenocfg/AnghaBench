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
typedef  int /*<<< orphan*/  ZSTDv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv07_checkContinuity (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ZSTDv07_copyDCtx (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 size_t ZSTDv07_decompressFrame (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

__attribute__((used)) static size_t ZSTDv07_decompress_usingPreparedDCtx(ZSTDv07_DCtx* dctx, const ZSTDv07_DCtx* refDCtx,
                                         void* dst, size_t dstCapacity,
                                   const void* src, size_t srcSize)
{
    ZSTDv07_copyDCtx(dctx, refDCtx);
    ZSTDv07_checkContinuity(dctx, dst);
    return ZSTDv07_decompressFrame(dctx, dst, dstCapacity, src, srcSize);
}