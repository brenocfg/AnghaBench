#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nbWorkers; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mtctx; TYPE_1__ appliedParams; } ;
typedef  TYPE_2__ ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTDMT_nextInputSizeHint (int /*<<< orphan*/ *) ; 
 size_t ZSTD_nextInputSizeHint (TYPE_2__ const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_nextInputSizeHint_MTorST(const ZSTD_CCtx* cctx)
{
#ifdef ZSTD_MULTITHREAD
    if (cctx->appliedParams.nbWorkers >= 1) {
        assert(cctx->mtctx != NULL);
        return ZSTDMT_nextInputSizeHint(cctx->mtctx);
    }
#endif
    return ZSTD_nextInputSizeHint(cctx);

}