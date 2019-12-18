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
 scalar_t__ BLOCKSIZE ; 
 scalar_t__ WILDCOPY_OVERLENGTH ; 
 scalar_t__ ZSTDv05_frameHeaderSize_max ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

void ZSTDv05_copyDCtx(ZSTDv05_DCtx* dstDCtx, const ZSTDv05_DCtx* srcDCtx)
{
    memcpy(dstDCtx, srcDCtx,
           sizeof(ZSTDv05_DCtx) - (BLOCKSIZE+WILDCOPY_OVERLENGTH + ZSTDv05_frameHeaderSize_max));  /* no need to copy workspace */
}