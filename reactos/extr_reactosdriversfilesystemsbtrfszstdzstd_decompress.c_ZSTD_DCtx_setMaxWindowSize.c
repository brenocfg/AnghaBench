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
struct TYPE_3__ {scalar_t__ streamStage; size_t maxWindowSize; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zdss_init ; 

size_t ZSTD_DCtx_setMaxWindowSize(ZSTD_DCtx* dctx, size_t maxWindowSize)
{
    if (dctx->streamStage != zdss_init) return ERROR(stage_wrong);
    dctx->maxWindowSize = maxWindowSize;
    return 0;
}