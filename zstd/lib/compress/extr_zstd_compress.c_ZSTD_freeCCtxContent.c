#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ staticSize; int /*<<< orphan*/  customMem; int /*<<< orphan*/  workspace; int /*<<< orphan*/ * mtctx; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDMT_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_clearAllDicts (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_cwksp_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void ZSTD_freeCCtxContent(ZSTD_CCtx* cctx)
{
    assert(cctx != NULL);
    assert(cctx->staticSize == 0);
    ZSTD_clearAllDicts(cctx);
#ifdef ZSTD_MULTITHREAD
    ZSTDMT_freeCCtx(cctx->mtctx); cctx->mtctx = NULL;
#endif
    ZSTD_cwksp_free(&cctx->workspace, cctx->customMem);
}