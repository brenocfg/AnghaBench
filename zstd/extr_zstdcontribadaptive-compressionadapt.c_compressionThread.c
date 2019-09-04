#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {size_t size; scalar_t__ capacity; scalar_t__ start; } ;
struct TYPE_31__ {size_t size; size_t const start; } ;
struct TYPE_25__ {size_t compressedSize; size_t const dictSize; unsigned int lastJobPlusOne; TYPE_6__ dst; TYPE_4__ src; } ;
typedef  TYPE_14__ jobDescription ;
struct TYPE_35__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_34__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_32__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_29__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_24__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_28__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_23__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_22__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_21__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_36__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_26__ {unsigned int numJobs; unsigned int jobReadyID; unsigned int jobWriteID; unsigned int compressWaitCreateCompletion; unsigned int createCompletion; unsigned int compressWaitWriteCompletion; unsigned int writeCompletion; int compressionCompletion; unsigned int compressionLevel; scalar_t__ threadError; TYPE_8__ jobCompressed_mutex; TYPE_7__ jobCompressed_cond; int /*<<< orphan*/  jobCompressedID; TYPE_5__ compressionCompletion_mutex; int /*<<< orphan*/  cctx; TYPE_2__ compressionLevel_mutex; TYPE_13__ jobWrite_mutex; TYPE_1__ jobWrite_cond; TYPE_12__ jobReady_mutex; TYPE_11__ jobReady_cond; TYPE_10__ writeCompletion_mutex; TYPE_9__ createCompletion_mutex; TYPE_14__* jobs; } ;
typedef  TYPE_15__ adaptCCtx ;
struct TYPE_30__ {int windowLog; } ;
struct TYPE_27__ {TYPE_3__ cParams; } ;
typedef  TYPE_16__ ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 size_t MIN (size_t,size_t const) ; 
 size_t ZSTD_BLOCKSIZE_MAX ; 
 size_t ZSTD_CCtx_setParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_forceMaxWindow ; 
 size_t ZSTD_compressBegin_advanced (int /*<<< orphan*/ ,size_t const,size_t const,TYPE_16__,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressContinue (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t const,size_t const) ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t const,size_t const) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t const) ; 
 TYPE_16__ ZSTD_getParams (unsigned int,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  ZSTD_invalidateRepCodes (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  adaptCompressionLevel (TYPE_15__* const) ; 
 size_t getUseableDictSize (unsigned int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signalErrorToThreads (TYPE_15__* const) ; 

__attribute__((used)) static void* compressionThread(void* arg)
{
    adaptCCtx* const ctx = (adaptCCtx*)arg;
    unsigned currJob = 0;
    for ( ; ; ) {
        unsigned const currJobIndex = currJob % ctx->numJobs;
        jobDescription* const job = &ctx->jobs[currJobIndex];
        DEBUG(2, "starting compression for job %u\n", currJob);

        {
            /* check if compression thread will have to wait */
            unsigned willWaitForCreate = 0;
            unsigned willWaitForWrite = 0;

            pthread_mutex_lock(&ctx->jobReady_mutex.pMutex);
            if (currJob + 1 > ctx->jobReadyID) willWaitForCreate = 1;
            pthread_mutex_unlock(&ctx->jobReady_mutex.pMutex);

            pthread_mutex_lock(&ctx->jobWrite_mutex.pMutex);
            if (currJob - ctx->jobWriteID >= ctx->numJobs) willWaitForWrite = 1;
            pthread_mutex_unlock(&ctx->jobWrite_mutex.pMutex);


            pthread_mutex_lock(&ctx->createCompletion_mutex.pMutex);
            if (willWaitForCreate) {
                DEBUG(2, "compression will wait for create on job %u\n", currJob);
                ctx->compressWaitCreateCompletion = ctx->createCompletion;
                DEBUG(2, "create completion %f\n", ctx->compressWaitCreateCompletion);

            }
            else {
                ctx->compressWaitCreateCompletion = 1;
            }
            pthread_mutex_unlock(&ctx->createCompletion_mutex.pMutex);

            pthread_mutex_lock(&ctx->writeCompletion_mutex.pMutex);
            if (willWaitForWrite) {
                DEBUG(2, "compression will wait for write on job %u\n", currJob);
                ctx->compressWaitWriteCompletion = ctx->writeCompletion;
                DEBUG(2, "write completion %f\n", ctx->compressWaitWriteCompletion);
            }
            else {
                ctx->compressWaitWriteCompletion = 1;
            }
            pthread_mutex_unlock(&ctx->writeCompletion_mutex.pMutex);

        }

        /* wait until job is ready */
        pthread_mutex_lock(&ctx->jobReady_mutex.pMutex);
        while (currJob + 1 > ctx->jobReadyID && !ctx->threadError) {
            pthread_cond_wait(&ctx->jobReady_cond.pCond, &ctx->jobReady_mutex.pMutex);
        }
        pthread_mutex_unlock(&ctx->jobReady_mutex.pMutex);

        /* wait until job previously in this space is written */
        pthread_mutex_lock(&ctx->jobWrite_mutex.pMutex);
        while (currJob - ctx->jobWriteID >= ctx->numJobs && !ctx->threadError) {
            pthread_cond_wait(&ctx->jobWrite_cond.pCond, &ctx->jobWrite_mutex.pMutex);
        }
        pthread_mutex_unlock(&ctx->jobWrite_mutex.pMutex);
        /* reset compression completion */
        pthread_mutex_lock(&ctx->compressionCompletion_mutex.pMutex);
        ctx->compressionCompletion = 0;
        pthread_mutex_unlock(&ctx->compressionCompletion_mutex.pMutex);

        /* adapt compression level */
        if (currJob) adaptCompressionLevel(ctx);

        pthread_mutex_lock(&ctx->compressionLevel_mutex.pMutex);
        DEBUG(2, "job %u compressed with level %u\n", currJob, ctx->compressionLevel);
        pthread_mutex_unlock(&ctx->compressionLevel_mutex.pMutex);

        /* compress the data */
        {
            size_t const compressionBlockSize = ZSTD_BLOCKSIZE_MAX; /* 128 KB */
            unsigned cLevel;
            unsigned blockNum = 0;
            size_t remaining = job->src.size;
            size_t srcPos = 0;
            size_t dstPos = 0;

            pthread_mutex_lock(&ctx->compressionLevel_mutex.pMutex);
            cLevel = ctx->compressionLevel;
            pthread_mutex_unlock(&ctx->compressionLevel_mutex.pMutex);

            /* reset compressed size */
            job->compressedSize = 0;
            DEBUG(2, "calling ZSTD_compressBegin()\n");
            /* begin compression */
            {
                size_t const useDictSize = MIN(getUseableDictSize(cLevel), job->dictSize);
                ZSTD_parameters params = ZSTD_getParams(cLevel, 0, useDictSize);
                params.cParams.windowLog = 23;
                {
                    size_t const initError = ZSTD_compressBegin_advanced(ctx->cctx, job->src.start + job->dictSize - useDictSize, useDictSize, params, 0);
                    size_t const windowSizeError = ZSTD_CCtx_setParameter(ctx->cctx, ZSTD_c_forceMaxWindow, 1);
                    if (ZSTD_isError(initError) || ZSTD_isError(windowSizeError)) {
                        DISPLAY("Error: something went wrong while starting compression\n");
                        signalErrorToThreads(ctx);
                        return arg;
                    }
                }
            }
            DEBUG(2, "finished with ZSTD_compressBegin()\n");

            do {
                size_t const actualBlockSize = MIN(remaining, compressionBlockSize);

                /* continue compression */
                if (currJob != 0 || blockNum != 0) { /* not first block of first job flush/overwrite the frame header */
                    size_t const hSize = ZSTD_compressContinue(ctx->cctx, job->dst.start + dstPos, job->dst.capacity - dstPos, job->src.start + job->dictSize + srcPos, 0);
                    if (ZSTD_isError(hSize)) {
                        DISPLAY("Error: something went wrong while continuing compression\n");
                        job->compressedSize = hSize;
                        signalErrorToThreads(ctx);
                        return arg;
                    }
                    ZSTD_invalidateRepCodes(ctx->cctx);
                }
                {
                    size_t const ret = (job->lastJobPlusOne == currJob + 1 && remaining == actualBlockSize) ?
                                            ZSTD_compressEnd     (ctx->cctx, job->dst.start + dstPos, job->dst.capacity - dstPos, job->src.start + job->dictSize + srcPos, actualBlockSize) :
                                            ZSTD_compressContinue(ctx->cctx, job->dst.start + dstPos, job->dst.capacity - dstPos, job->src.start + job->dictSize + srcPos, actualBlockSize);
                    if (ZSTD_isError(ret)) {
                        DISPLAY("Error: something went wrong during compression: %s\n", ZSTD_getErrorName(ret));
                        signalErrorToThreads(ctx);
                        return arg;
                    }
                    job->compressedSize += ret;
                    remaining -= actualBlockSize;
                    srcPos += actualBlockSize;
                    dstPos += ret;
                    blockNum++;

                    /* update completion */
                    pthread_mutex_lock(&ctx->compressionCompletion_mutex.pMutex);
                    ctx->compressionCompletion = 1 - (double)remaining/job->src.size;
                    pthread_mutex_unlock(&ctx->compressionCompletion_mutex.pMutex);
                }
            } while (remaining != 0);
            job->dst.size = job->compressedSize;
        }
        pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
        ctx->jobCompressedID++;
        pthread_cond_broadcast(&ctx->jobCompressed_cond.pCond);
        pthread_mutex_unlock(&ctx->jobCompressed_mutex.pMutex);
        if (job->lastJobPlusOne == currJob + 1 || ctx->threadError) {
            /* finished compressing all jobs */
            break;
        }
        DEBUG(2, "finished compressing job %u\n", currJob);
        currJob++;
    }
    return arg;
}