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
struct TYPE_3__ {int /*<<< orphan*/  refContext; } ;
typedef  TYPE_1__ ZSTDv07_DDict ;
typedef  int /*<<< orphan*/  ZSTDv07_DCtx ;

/* Variables and functions */
 size_t ZSTDv07_decompress_usingPreparedDCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 

size_t ZSTDv07_decompress_usingDDict(ZSTDv07_DCtx* dctx,
                                           void* dst, size_t dstCapacity,
                                     const void* src, size_t srcSize,
                                     const ZSTDv07_DDict* ddict)
{
    return ZSTDv07_decompress_usingPreparedDCtx(dctx, ddict->refContext,
                                           dst, dstCapacity,
                                           src, srcSize);
}