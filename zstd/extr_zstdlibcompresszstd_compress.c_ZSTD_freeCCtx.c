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
struct TYPE_5__ {int /*<<< orphan*/  customMem; int /*<<< orphan*/  staticSize; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCCtxContent (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTD_freeCCtx(ZSTD_CCtx* cctx)
{
    if (cctx==NULL) return 0;   /* support free on NULL */
    RETURN_ERROR_IF(cctx->staticSize, memory_allocation,
                    "not compatible with static CCtx");
    ZSTD_freeCCtxContent(cctx);
    ZSTD_free(cctx, cctx->customMem);
    return 0;
}