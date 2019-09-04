#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_17__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_16__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_15__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_14__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_13__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_12__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_11__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_19__ {int threadError; TYPE_8__ allJobsCompleted_mutex; TYPE_7__ allJobsCompleted_cond; TYPE_6__ jobWrite_mutex; TYPE_5__ jobWrite_cond; TYPE_4__ jobReady_mutex; TYPE_3__ jobCompressed_cond; TYPE_2__ jobCompressed_mutex; TYPE_1__ jobReady_cond; } ;
typedef  TYPE_9__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void signalErrorToThreads(adaptCCtx* ctx)
{
    ctx->threadError = 1;
    pthread_mutex_lock(&ctx->jobReady_mutex.pMutex);
    pthread_cond_signal(&ctx->jobReady_cond.pCond);
    pthread_mutex_unlock(&ctx->jobReady_mutex.pMutex);

    pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
    pthread_cond_broadcast(&ctx->jobCompressed_cond.pCond);
    pthread_mutex_unlock(&ctx->jobReady_mutex.pMutex);

    pthread_mutex_lock(&ctx->jobWrite_mutex.pMutex);
    pthread_cond_signal(&ctx->jobWrite_cond.pCond);
    pthread_mutex_unlock(&ctx->jobWrite_mutex.pMutex);

    pthread_mutex_lock(&ctx->allJobsCompleted_mutex.pMutex);
    pthread_cond_signal(&ctx->allJobsCompleted_cond.pCond);
    pthread_mutex_unlock(&ctx->allJobsCompleted_mutex.pMutex);
}