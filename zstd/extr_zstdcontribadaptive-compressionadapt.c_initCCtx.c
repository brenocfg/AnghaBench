#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int capacity; void* start; } ;
struct TYPE_9__ {int capacity; void* start; } ;
struct TYPE_13__ {TYPE_2__ dst; TYPE_1__ src; scalar_t__ lastJobPlusOne; } ;
typedef  TYPE_5__ jobDescription ;
struct TYPE_11__ {int capacity; void* start; } ;
struct TYPE_12__ {TYPE_3__ buffer; scalar_t__ filled; } ;
struct TYPE_14__ {unsigned int numJobs; int createWaitCompressionCompletion; int compressWaitCreateCompletion; int compressWaitWriteCompletion; int writeWaitCompressionCompletion; int createCompletion; int writeCompletion; int compressionCompletion; TYPE_4__ input; int /*<<< orphan*/  cctx; scalar_t__ allJobsCompleted; scalar_t__ threadError; scalar_t__ nextJobID; TYPE_5__* jobs; scalar_t__ cooldown; scalar_t__ convergenceCounter; scalar_t__ lastDictSize; scalar_t__ jobWriteID; scalar_t__ jobCompressedID; scalar_t__ jobReadyID; int /*<<< orphan*/  compressionLevel_mutex; int /*<<< orphan*/  writeCompletion_mutex; int /*<<< orphan*/  createCompletion_mutex; int /*<<< orphan*/  compressionCompletion_mutex; int /*<<< orphan*/  jobWrite_cond; int /*<<< orphan*/  jobWrite_mutex; int /*<<< orphan*/  allJobsCompleted_cond; int /*<<< orphan*/  allJobsCompleted_mutex; int /*<<< orphan*/  jobReady_cond; int /*<<< orphan*/  jobReady_mutex; int /*<<< orphan*/  jobCompressed_cond; int /*<<< orphan*/  jobCompressed_mutex; int /*<<< orphan*/  compressionLevel; } ;
typedef  TYPE_6__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int FILE_CHUNK_SIZE ; 
 int ZSTD_compressBound (int) ; 
 int /*<<< orphan*/  ZSTD_createCCtx () ; 
 TYPE_5__* calloc (int,unsigned int) ; 
 int /*<<< orphan*/  g_compressionLevel ; 
 int initCond (int /*<<< orphan*/ *) ; 
 int initMutex (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 

__attribute__((used)) static int initCCtx(adaptCCtx* ctx, unsigned numJobs)
{
    ctx->compressionLevel = g_compressionLevel;
    {
        int pthreadError = 0;
        pthreadError |= initMutex(&ctx->jobCompressed_mutex);
        pthreadError |= initCond(&ctx->jobCompressed_cond);
        pthreadError |= initMutex(&ctx->jobReady_mutex);
        pthreadError |= initCond(&ctx->jobReady_cond);
        pthreadError |= initMutex(&ctx->allJobsCompleted_mutex);
        pthreadError |= initCond(&ctx->allJobsCompleted_cond);
        pthreadError |= initMutex(&ctx->jobWrite_mutex);
        pthreadError |= initCond(&ctx->jobWrite_cond);
        pthreadError |= initMutex(&ctx->compressionCompletion_mutex);
        pthreadError |= initMutex(&ctx->createCompletion_mutex);
        pthreadError |= initMutex(&ctx->writeCompletion_mutex);
        pthreadError |= initMutex(&ctx->compressionLevel_mutex);
        if (pthreadError) return pthreadError;
    }
    ctx->numJobs = numJobs;
    ctx->jobReadyID = 0;
    ctx->jobCompressedID = 0;
    ctx->jobWriteID = 0;
    ctx->lastDictSize = 0;


    ctx->createWaitCompressionCompletion = 1;
    ctx->compressWaitCreateCompletion = 1;
    ctx->compressWaitWriteCompletion = 1;
    ctx->writeWaitCompressionCompletion = 1;
    ctx->createCompletion = 1;
    ctx->writeCompletion = 1;
    ctx->compressionCompletion = 1;
    ctx->convergenceCounter = 0;
    ctx->cooldown = 0;

    ctx->jobs = calloc(1, numJobs*sizeof(jobDescription));

    if (!ctx->jobs) {
        DISPLAY("Error: could not allocate space for jobs during context creation\n");
        return 1;
    }

    /* initializing jobs */
    {
        unsigned jobNum;
        for (jobNum=0; jobNum<numJobs; jobNum++) {
            jobDescription* job = &ctx->jobs[jobNum];
            job->src.start = malloc(2 * FILE_CHUNK_SIZE);
            job->dst.start = malloc(ZSTD_compressBound(FILE_CHUNK_SIZE));
            job->lastJobPlusOne = 0;
            if (!job->src.start || !job->dst.start) {
                DISPLAY("Could not allocate buffers for jobs\n");
                return 1;
            }
            job->src.capacity = FILE_CHUNK_SIZE;
            job->dst.capacity = ZSTD_compressBound(FILE_CHUNK_SIZE);
        }
    }

    ctx->nextJobID = 0;
    ctx->threadError = 0;
    ctx->allJobsCompleted = 0;

    ctx->cctx = ZSTD_createCCtx();
    if (!ctx->cctx) {
        DISPLAY("Error: could not allocate ZSTD_CCtx\n");
        return 1;
    }

    ctx->input.filled = 0;
    ctx->input.buffer.capacity = 2 * FILE_CHUNK_SIZE;

    ctx->input.buffer.start = malloc(ctx->input.buffer.capacity);
    if (!ctx->input.buffer.start) {
        DISPLAY("Error: could not allocate input buffer\n");
        return 1;
    }
    return 0;
}