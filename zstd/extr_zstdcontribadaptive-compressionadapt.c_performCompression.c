#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_19__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_17__ {scalar_t__ start; } ;
struct TYPE_18__ {scalar_t__ filled; TYPE_4__ buffer; } ;
struct TYPE_16__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_15__ {int /*<<< orphan*/  pCond; } ;
struct TYPE_14__ {int /*<<< orphan*/  pMutex; } ;
struct TYPE_20__ {unsigned int nextJobID; unsigned int const jobCompressedID; unsigned int const numJobs; int createWaitCompressionCompletion; int compressionCompletion; int createCompletion; TYPE_6__ createCompletion_mutex; TYPE_5__ input; TYPE_3__ jobCompressed_mutex; TYPE_2__ jobCompressed_cond; int /*<<< orphan*/  threadError; TYPE_1__ compressionCompletion_mutex; } ;
typedef  TYPE_7__ outputThreadArg ;
typedef  TYPE_7__ adaptCCtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,unsigned int const,...) ; 
 int /*<<< orphan*/  DISPLAY (char*) ; 
 size_t FILE_CHUNK_SIZE ; 
 int /*<<< orphan*/  compressionThread ; 
 int createCompressionJob (TYPE_7__*,size_t,int const) ; 
 int feof (int /*<<< orphan*/ * const) ; 
 size_t fread (scalar_t__,int,size_t const,int /*<<< orphan*/ * const) ; 
 size_t g_streamedSize ; 
 int /*<<< orphan*/  outputThread ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signalErrorToThreads (TYPE_7__*) ; 

__attribute__((used)) static int performCompression(adaptCCtx* ctx, FILE* const srcFile, outputThreadArg* otArg)
{
    /* early error check to exit */
    if (!ctx || !srcFile || !otArg) {
        return 1;
    }

    /* create output thread */
    {
        pthread_t out;
        if (pthread_create(&out, NULL, &outputThread, otArg)) {
            DISPLAY("Error: could not create output thread\n");
            signalErrorToThreads(ctx);
            return 1;
        }
        else if (pthread_detach(out)) {
        	DISPLAY("Error: could not detach output thread\n");
        	signalErrorToThreads(ctx);
        	return 1;
        }
    }

    /* create compression thread */
    {
        pthread_t compression;
        if (pthread_create(&compression, NULL, &compressionThread, ctx)) {
            DISPLAY("Error: could not create compression thread\n");
            signalErrorToThreads(ctx);
            return 1;
        }
        else if (pthread_detach(compression)) {
        	DISPLAY("Error: could not detach compression thread\n");
        	signalErrorToThreads(ctx);
        	return 1;
        }
    }
    {
        unsigned currJob = 0;
        /* creating jobs */
        for ( ; ; ) {
            size_t pos = 0;
            size_t const readBlockSize = 1 << 15;
            size_t remaining = FILE_CHUNK_SIZE;
            unsigned const nextJob = ctx->nextJobID;
            unsigned willWaitForCompress = 0;
            DEBUG(2, "starting creation of job %u\n", currJob);

            pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
            if (nextJob - ctx->jobCompressedID >= ctx->numJobs) willWaitForCompress = 1;
            pthread_mutex_unlock(&ctx->jobCompressed_mutex.pMutex);

            pthread_mutex_lock(&ctx->compressionCompletion_mutex.pMutex);
            if (willWaitForCompress) {
                /* creation thread is waiting, take measurement of completion */
                ctx->createWaitCompressionCompletion = ctx->compressionCompletion;
                DEBUG(2, "create thread waiting for nextJob: %u, createWaitCompressionCompletion %f\n", nextJob, ctx->createWaitCompressionCompletion);
            }
            else {
                ctx->createWaitCompressionCompletion = 1;
            }
            pthread_mutex_unlock(&ctx->compressionCompletion_mutex.pMutex);

            /* wait until the job has been compressed */
            pthread_mutex_lock(&ctx->jobCompressed_mutex.pMutex);
            while (nextJob - ctx->jobCompressedID >= ctx->numJobs && !ctx->threadError) {
                pthread_cond_wait(&ctx->jobCompressed_cond.pCond, &ctx->jobCompressed_mutex.pMutex);
            }
            pthread_mutex_unlock(&ctx->jobCompressed_mutex.pMutex);

            /* reset create completion */
            pthread_mutex_lock(&ctx->createCompletion_mutex.pMutex);
            ctx->createCompletion = 0;
            pthread_mutex_unlock(&ctx->createCompletion_mutex.pMutex);

            while (remaining != 0 && !feof(srcFile)) {
                size_t const ret = fread(ctx->input.buffer.start + ctx->input.filled + pos, 1, readBlockSize, srcFile);
                if (ret != readBlockSize && !feof(srcFile)) {
                    /* error could not read correct number of bytes */
                    DISPLAY("Error: problem occurred during read from src file\n");
                    signalErrorToThreads(ctx);
                    return 1;
                }
                pos += ret;
                remaining -= ret;
                pthread_mutex_lock(&ctx->createCompletion_mutex.pMutex);
                ctx->createCompletion = 1 - (double)remaining/((size_t)FILE_CHUNK_SIZE);
                pthread_mutex_unlock(&ctx->createCompletion_mutex.pMutex);
            }
            if (remaining != 0 && !feof(srcFile)) {
                DISPLAY("Error: problem occurred during read from src file\n");
                signalErrorToThreads(ctx);
                return 1;
            }
            g_streamedSize += pos;
            /* reading was fine, now create the compression job */
            {
                int const last = feof(srcFile);
                int const error = createCompressionJob(ctx, pos, last);
                if (error != 0) {
                    signalErrorToThreads(ctx);
                    return error;
                }
            }
            DEBUG(2, "finished creating job %u\n", currJob);
            currJob++;
            if (feof(srcFile)) {
                break;
            }
        }
    }
    /* success -- created all jobs */
    return 0;
}