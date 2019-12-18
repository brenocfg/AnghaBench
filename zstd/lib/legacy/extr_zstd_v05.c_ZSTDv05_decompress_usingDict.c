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
 int /*<<< orphan*/  ZSTDv05_checkContinuity (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ZSTDv05_decompressBegin_usingDict (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTDv05_decompress_continueDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

size_t ZSTDv05_decompress_usingDict(ZSTDv05_DCtx* dctx,
                                 void* dst, size_t maxDstSize,
                                 const void* src, size_t srcSize,
                                 const void* dict, size_t dictSize)
{
    ZSTDv05_decompressBegin_usingDict(dctx, dict, dictSize);
    ZSTDv05_checkContinuity(dctx, dst);
    return ZSTDv05_decompress_continueDCtx(dctx, dst, maxDstSize, src, srcSize);
}