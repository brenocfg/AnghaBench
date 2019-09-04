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
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
struct TYPE_3__ {scalar_t__ streamStage; int cdict; int /*<<< orphan*/  requestedParams; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_setParametersUsingCCtxParams(
        ZSTD_CCtx* cctx, const ZSTD_CCtx_params* params)
{
    DEBUGLOG(4, "ZSTD_CCtx_setParametersUsingCCtxParams");
    RETURN_ERROR_IF(cctx->streamStage != zcss_init, stage_wrong);
    RETURN_ERROR_IF(cctx->cdict, stage_wrong);

    cctx->requestedParams = *params;
    return 0;
}