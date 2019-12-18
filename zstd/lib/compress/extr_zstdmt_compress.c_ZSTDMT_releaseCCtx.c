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
struct TYPE_3__ {scalar_t__ availCCtx; scalar_t__ totalCCtx; int /*<<< orphan*/  poolMutex; int /*<<< orphan*/ ** cctx; } ;
typedef  TYPE_1__ ZSTDMT_CCtxPool ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_releaseCCtx(ZSTDMT_CCtxPool* pool, ZSTD_CCtx* cctx)
{
    if (cctx==NULL) return;   /* compatibility with release on NULL */
    ZSTD_pthread_mutex_lock(&pool->poolMutex);
    if (pool->availCCtx < pool->totalCCtx)
        pool->cctx[pool->availCCtx++] = cctx;
    else {
        /* pool overflow : should not happen, since totalCCtx==nbWorkers */
        DEBUGLOG(4, "CCtx pool overflow : free cctx");
        ZSTD_freeCCtx(cctx);
    }
    ZSTD_pthread_mutex_unlock(&pool->poolMutex);
}