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
struct TYPE_3__ {void* base; } ;
typedef  TYPE_1__ dctx_t ;

/* Variables and functions */
 size_t ZSTDv01_decompressDCtx (TYPE_1__*,void*,size_t,void const*,size_t) ; 

size_t ZSTDv01_decompress(void* dst, size_t maxDstSize, const void* src, size_t srcSize)
{
    dctx_t ctx;
    ctx.base = dst;
    return ZSTDv01_decompressDCtx(&ctx, dst, maxDstSize, src, srcSize);
}