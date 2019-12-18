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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
struct TYPE_3__ {unsigned int totalCCtx; int /*<<< orphan*/  poolMutex; int /*<<< orphan*/ * cctx; } ;
typedef  TYPE_1__ ZSTDMT_CCtxPool ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_sizeof_CCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t ZSTDMT_sizeof_CCtxPool(ZSTDMT_CCtxPool* cctxPool)
{
    ZSTD_pthread_mutex_lock(&cctxPool->poolMutex);
    {   unsigned const nbWorkers = cctxPool->totalCCtx;
        size_t const poolSize = sizeof(*cctxPool)
                                + (nbWorkers-1) * sizeof(ZSTD_CCtx*);
        unsigned u;
        size_t totalCCtxSize = 0;
        for (u=0; u<nbWorkers; u++) {
            totalCCtxSize += ZSTD_sizeof_CCtx(cctxPool->cctx[u]);
        }
        ZSTD_pthread_mutex_unlock(&cctxPool->poolMutex);
        assert(nbWorkers > 0);
        return poolSize + totalCCtxSize;
    }
}