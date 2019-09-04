#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* start; } ;
struct TYPE_8__ {TYPE_1__ buffer; } ;
struct TYPE_9__ {struct TYPE_9__* jobs; TYPE_2__ input; int /*<<< orphan*/  cctx; int /*<<< orphan*/  compressionLevel_mutex; int /*<<< orphan*/  writeCompletion_mutex; int /*<<< orphan*/  createCompletion_mutex; int /*<<< orphan*/  compressionCompletion_mutex; int /*<<< orphan*/  jobWrite_cond; int /*<<< orphan*/  jobWrite_mutex; int /*<<< orphan*/  allJobsCompleted_cond; int /*<<< orphan*/  allJobsCompleted_mutex; int /*<<< orphan*/  jobReady_cond; int /*<<< orphan*/  jobReady_mutex; int /*<<< orphan*/  jobCompressed_cond; int /*<<< orphan*/  jobCompressed_mutex; } ;
typedef  TYPE_3__ adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ ) ; 
 int ZSTD_isError (int /*<<< orphan*/ ) ; 
 int destroyCond (int /*<<< orphan*/ *) ; 
 int destroyMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  freeCompressionJobs (TYPE_3__*) ; 

__attribute__((used)) static int freeCCtx(adaptCCtx* ctx)
{
    if (!ctx) return 0;
    {
        int error = 0;
        error |= destroyMutex(&ctx->jobCompressed_mutex);
        error |= destroyCond(&ctx->jobCompressed_cond);
        error |= destroyMutex(&ctx->jobReady_mutex);
        error |= destroyCond(&ctx->jobReady_cond);
        error |= destroyMutex(&ctx->allJobsCompleted_mutex);
        error |= destroyCond(&ctx->allJobsCompleted_cond);
        error |= destroyMutex(&ctx->jobWrite_mutex);
        error |= destroyCond(&ctx->jobWrite_cond);
        error |= destroyMutex(&ctx->compressionCompletion_mutex);
        error |= destroyMutex(&ctx->createCompletion_mutex);
        error |= destroyMutex(&ctx->writeCompletion_mutex);
        error |= destroyMutex(&ctx->compressionLevel_mutex);
        error |= ZSTD_isError(ZSTD_freeCCtx(ctx->cctx));
        free(ctx->input.buffer.start);
        if (ctx->jobs){
            freeCompressionJobs(ctx);
            free(ctx->jobs);
        }
        free(ctx);
        return error;
    }
}