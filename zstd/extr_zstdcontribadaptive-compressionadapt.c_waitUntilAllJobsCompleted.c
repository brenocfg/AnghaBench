#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_7__ {scalar_t__ allJobsCompleted; TYPE_2__ allJobsCompleted_mutex; TYPE_1__ allJobsCompleted_cond; int /*<<< orphan*/  threadError; } ;
typedef  TYPE_3__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void waitUntilAllJobsCompleted(adaptCCtx* ctx)
{
    if (!ctx) return;
    pthread_mutex_lock(&ctx->allJobsCompleted_mutex.pMutex);
    while (ctx->allJobsCompleted == 0 && !ctx->threadError) {
        pthread_cond_wait(&ctx->allJobsCompleted_cond.pCond, &ctx->allJobsCompleted_mutex.pMutex);
    }
    pthread_mutex_unlock(&ctx->allJobsCompleted_mutex.pMutex);
}