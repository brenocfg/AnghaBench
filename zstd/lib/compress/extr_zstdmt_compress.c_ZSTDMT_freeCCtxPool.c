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
struct TYPE_4__ {int totalCCtx; int /*<<< orphan*/  cMem; int /*<<< orphan*/  poolMutex; int /*<<< orphan*/ * cctx; } ;
typedef  TYPE_1__ ZSTDMT_CCtxPool ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_freeCCtxPool(ZSTDMT_CCtxPool* pool)
{
    int cid;
    for (cid=0; cid<pool->totalCCtx; cid++)
        ZSTD_freeCCtx(pool->cctx[cid]);  /* note : compatible with free on NULL */
    ZSTD_pthread_mutex_destroy(&pool->poolMutex);
    ZSTD_free(pool, pool->cMem);
}