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
typedef  int /*<<< orphan*/  ZBUFFv04_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 size_t ZBUFF_decompressContinue (int /*<<< orphan*/ *,void*,size_t*,void const*,size_t*) ; 

size_t ZBUFFv04_decompressContinue(ZBUFFv04_DCtx* dctx, void* dst, size_t* maxDstSizePtr, const void* src, size_t* srcSizePtr)
{
    DEBUGLOG(5, "ZBUFFv04_decompressContinue");
    return ZBUFF_decompressContinue(dctx, dst, maxDstSizePtr, src, srcSizePtr);
}