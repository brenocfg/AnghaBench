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
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_3__ {scalar_t__ streamStage; int /*<<< orphan*/  prefixDict; int /*<<< orphan*/  const* cdict; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zcss_init ; 

size_t ZSTD_CCtx_refCDict(ZSTD_CCtx* cctx, const ZSTD_CDict* cdict)
{
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    cctx->cdict = cdict;
    memset(&cctx->prefixDict, 0, sizeof(cctx->prefixDict));  /* exclusive */
    return 0;
}