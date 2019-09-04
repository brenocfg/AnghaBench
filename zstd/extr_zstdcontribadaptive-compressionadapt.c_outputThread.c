#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * dstFile; TYPE_13__* ctx; } ;
typedef  TYPE_11__ outputThreadArg ;
struct TYPE_22__ {scalar_t__ start; } ;
struct TYPE_17__ {size_t compressedSize; unsigned int lastJobPlusOne; TYPE_4__ dst; } ;
typedef  TYPE_12__ jobDescription ;
struct TYPE_15__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_27__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_26__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_25__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_24__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_23__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_21__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_20__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_19__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_18__ {unsigned int numJobs; unsigned int jobCompressedID; int writeWaitCompressionCompletion; int compressionCompletion; int writeCompletion; unsigned int compressionLevel; int allJobsCompleted; TYPE_10__ allJobsCompleted_mutex; TYPE_9__ allJobsCompleted_cond; scalar_t__ threadError; TYPE_8__ jobWrite_mutex; TYPE_7__ jobWrite_cond; int /*<<< orphan*/  jobWriteID; TYPE_6__ compressionLevel_mutex; TYPE_5__ writeCompletion_mutex; TYPE_3__ jobCompressed_mutex; TYPE_2__ jobCompressed_cond; TYPE_1__ compressionCompletion_mutex; TYPE_12__* jobs; } ;
typedef  TYPE_13__ adaptCCtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  DISPLAY (char*) ; 
 size_t MAX (size_t const,int) ; 
 size_t MIN (size_t,size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  displayProgress (unsigned int,int) ; 
 size_t fwrite (scalar_t__,int,size_t const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signalErrorToThreads (TYPE_13__* const) ; 

__attribute__((used)) static void* outputThread(void* arg)
{
    outputThreadArg* const otArg = (outputThreadArg*)arg;
    adaptCCtx* const ctx = otArg->ctx;
    FILE* const dstFile = otArg->dstFile;

    unsigned currJob = 0;
    for ( ; ; ) {
        unsigned const currJobIndex = currJob % ctx->numJobs;
        jobDescription* const job = &ctx->jobs[currJobIndex];
        unsigned willWaitForCompress = 0;
        DEBUG(2, "starting write for job %u\n", currJob);

        pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
        if (currJob + 1 > ctx->jobCompressedID) willWaitForCompress = 1;
        pthread_mutex_unlock(&ctx->jobCompressed_mutex.pMutex);


        pthread_mutex_lock(&ctx->compressionCompletion_mutex.pMutex);
        if (willWaitForCompress) {
            /* write thread is waiting on compression thread */
            ctx->writeWaitCompressionCompletion = ctx->compressionCompletion;
            DEBUG(2, "writer thread waiting for nextJob: %u, writeWaitCompressionCompletion %f\n", currJob, ctx->writeWaitCompressionCompletion);
        }
        else {
            ctx->writeWaitCompressionCompletion = 1;
        }
        pthread_mutex_unlock(&ctx->compressionCompletion_mutex.pMutex);

        pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
        while (currJob + 1 > ctx->jobCompressedID && !ctx->threadError) {
            pthread_cond_wait(&ctx->jobCompressed_cond.pCond, &ctx->jobCompressed_mutex.pMutex);
        }
        pthread_mutex_unlock(&ctx->jobCompressed_mutex.pMutex);

        /* reset write completion */
        pthread_mutex_lock(&ctx->writeCompletion_mutex.pMutex);
        ctx->writeCompletion = 0;
        pthread_mutex_unlock(&ctx->writeCompletion_mutex.pMutex);

        {
            size_t const compressedSize = job->compressedSize;
            size_t remaining = compressedSize;
            if (ZSTD_isError(compressedSize)) {
                DISPLAY("Error: an error occurred during compression\n");
                signalErrorToThreads(ctx);
                return arg;
            }
            {
                size_t const blockSize = MAX(compressedSize >> 7, 1 << 10);
                size_t pos = 0;
                for ( ; ; ) {
                    size_t const writeSize = MIN(remaining, blockSize);
                    size_t const ret = fwrite(job->dst.start + pos, 1, writeSize, dstFile);
                    if (ret != writeSize) break;
                    pos += ret;
                    remaining -= ret;

                    /* update completion variable for writing */
                    pthread_mutex_lock(&ctx->writeCompletion_mutex.pMutex);
                    ctx->writeCompletion = 1 - (double)remaining/compressedSize;
                    pthread_mutex_unlock(&ctx->writeCompletion_mutex.pMutex);

                    if (remaining == 0) break;
                }
                if (pos != compressedSize) {
                    DISPLAY("Error: an error occurred during file write operation\n");
                    signalErrorToThreads(ctx);
                    return arg;
                }
            }
        }
        {
            unsigned cLevel;
            pthread_mutex_lock(&ctx->compressionLevel_mutex.pMutex);
            cLevel = ctx->compressionLevel;
            pthread_mutex_unlock(&ctx->compressionLevel_mutex.pMutex);
            displayProgress(cLevel, job->lastJobPlusOne == currJob + 1);
        }
        pthread_mutex_lock(&ctx->jobWrite_mutex.pMutex);
        ctx->jobWriteID++;
        pthread_cond_signal(&ctx->jobWrite_cond.pCond);
        pthread_mutex_unlock(&ctx->jobWrite_mutex.pMutex);

        if (job->lastJobPlusOne == currJob + 1 || ctx->threadError) {
            /* finished with all jobs */
            pthread_mutex_lock(&ctx->allJobsCompleted_mutex.pMutex);
            ctx->allJobsCompleted = 1;
            pthread_cond_signal(&ctx->allJobsCompleted_cond.pCond);
            pthread_mutex_unlock(&ctx->allJobsCompleted_mutex.pMutex);
            break;
        }
        DEBUG(2, "finished writing job %u\n", currJob);
        currJob++;

    }
    return arg;
}