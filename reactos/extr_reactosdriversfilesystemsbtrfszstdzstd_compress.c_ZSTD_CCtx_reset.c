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
struct TYPE_3__ {scalar_t__ pledgedSrcSizePlusOne; int /*<<< orphan*/  streamStage; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  zcss_init ; 

void ZSTD_CCtx_reset(ZSTD_CCtx* cctx)
{
    cctx->streamStage = zcss_init;
    cctx->pledgedSrcSizePlusOne = 0;
}