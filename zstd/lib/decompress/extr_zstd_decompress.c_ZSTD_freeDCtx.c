#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_5__ {int /*<<< orphan*/  previousLegacyVersion; scalar_t__ legacyContext; struct TYPE_5__* inBuff; int /*<<< orphan*/  customMem; int /*<<< orphan*/  staticSize; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ZSTD_clearDict (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_freeLegacyStreamContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTD_freeDCtx(ZSTD_DCtx* dctx)
{
    if (dctx==NULL) return 0;   /* support free on NULL */
    RETURN_ERROR_IF(dctx->staticSize, memory_allocation, "not compatible with static DCtx");
    {   ZSTD_customMem const cMem = dctx->customMem;
        ZSTD_clearDict(dctx);
        ZSTD_free(dctx->inBuff, cMem);
        dctx->inBuff = NULL;
#if defined(ZSTD_LEGACY_SUPPORT) && (ZSTD_LEGACY_SUPPORT >= 1)
        if (dctx->legacyContext)
            ZSTD_freeLegacyStreamContext(dctx->legacyContext, dctx->previousLegacyVersion);
#endif
        ZSTD_free(dctx, cMem);
        return 0;
    }
}