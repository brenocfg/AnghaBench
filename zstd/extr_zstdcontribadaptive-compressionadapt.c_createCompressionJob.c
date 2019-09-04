#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; void* start; } ;
struct TYPE_14__ {unsigned int jobID; unsigned int lastJobPlusOne; size_t dictSize; TYPE_2__ src; } ;
typedef  TYPE_6__ jobDescription ;
struct TYPE_13__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_12__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_9__ {void* start; } ;
struct TYPE_11__ {size_t filled; TYPE_1__ buffer; } ;
struct TYPE_15__ {unsigned int nextJobID; unsigned int const numJobs; size_t lastDictSize; TYPE_5__ jobReady_mutex; TYPE_4__ jobReady_cond; int /*<<< orphan*/  jobReadyID; TYPE_3__ input; TYPE_6__* jobs; } ;
typedef  TYPE_7__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int createCompressionJob(adaptCCtx* ctx, size_t srcSize, int last)
{
    unsigned const nextJob = ctx->nextJobID;
    unsigned const nextJobIndex = nextJob % ctx->numJobs;
    jobDescription* const job = &ctx->jobs[nextJobIndex];


    job->src.size = srcSize;
    job->jobID = nextJob;
    if (last) job->lastJobPlusOne = nextJob + 1;
    {
        /* swap buffer */
        void* const copy = job->src.start;
        job->src.start = ctx->input.buffer.start;
        ctx->input.buffer.start = copy;
    }
    job->dictSize = ctx->lastDictSize;

    ctx->nextJobID++;
    /* if not on the last job, reuse data as dictionary in next job */
    if (!last) {
        size_t const oldDictSize = ctx->lastDictSize;
        memcpy(ctx->input.buffer.start, job->src.start + oldDictSize, srcSize);
        ctx->lastDictSize = srcSize;
        ctx->input.filled = srcSize;
    }

    /* signal job ready */
    pthread_mutex_lock(&ctx->jobReady_mutex.pMutex);
    ctx->jobReadyID++;
    pthread_cond_signal(&ctx->jobReady_cond.pCond);
    pthread_mutex_unlock(&ctx->jobReady_mutex.pMutex);

    return 0;
}