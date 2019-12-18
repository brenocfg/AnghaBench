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
struct TYPE_3__ {scalar_t__ flagRepeatTable; int /*<<< orphan*/ * hufTableX4; int /*<<< orphan*/ * dictEnd; int /*<<< orphan*/ * vBase; int /*<<< orphan*/ * base; int /*<<< orphan*/ * previousDstEnd; int /*<<< orphan*/  stage; int /*<<< orphan*/  expected; } ;
typedef  TYPE_1__ ZSTDv06_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  HufLog ; 
 int /*<<< orphan*/  ZSTDds_getFrameHeaderSize ; 
 int /*<<< orphan*/  ZSTDv06_frameHeaderSize_min ; 

size_t ZSTDv06_decompressBegin(ZSTDv06_DCtx* dctx)
{
    dctx->expected = ZSTDv06_frameHeaderSize_min;
    dctx->stage = ZSTDds_getFrameHeaderSize;
    dctx->previousDstEnd = NULL;
    dctx->base = NULL;
    dctx->vBase = NULL;
    dctx->dictEnd = NULL;
    dctx->hufTableX4[0] = HufLog;
    dctx->flagRepeatTable = 0;
    return 0;
}