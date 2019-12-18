#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int enableLdm; } ;
struct TYPE_12__ {scalar_t__ checksumFlag; } ;
struct TYPE_13__ {scalar_t__ jobSize; TYPE_8__ ldmParams; TYPE_1__ fParams; } ;
struct TYPE_17__ {int /*<<< orphan*/  window; } ;
struct TYPE_14__ {unsigned int nextJobID; TYPE_2__ params; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  xxhState; int /*<<< orphan*/  ldmWindowMutex; int /*<<< orphan*/  ldmWindowCond; TYPE_6__ ldmState; int /*<<< orphan*/  ldmWindow; } ;
typedef  TYPE_3__ serialState_t ;
struct TYPE_15__ {scalar_t__ pos; scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/ * seq; } ;
typedef  TYPE_4__ rawSeqStore_t ;
struct TYPE_16__ {scalar_t__ size; int /*<<< orphan*/  start; } ;
typedef  TYPE_5__ range_t ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ZSTD_PTHREAD_MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t const) ; 
 size_t ZSTD_ldm_generateSequences (TYPE_6__*,TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t ZSTD_referenceExternalSequences (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ZSTD_window_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void ZSTDMT_serialState_update(serialState_t* serialState,
                                      ZSTD_CCtx* jobCCtx, rawSeqStore_t seqStore,
                                      range_t src, unsigned jobID)
{
    /* Wait for our turn */
    ZSTD_PTHREAD_MUTEX_LOCK(&serialState->mutex);
    while (serialState->nextJobID < jobID) {
        DEBUGLOG(5, "wait for serialState->cond");
        ZSTD_pthread_cond_wait(&serialState->cond, &serialState->mutex);
    }
    /* A future job may error and skip our job */
    if (serialState->nextJobID == jobID) {
        /* It is now our turn, do any processing necessary */
        if (serialState->params.ldmParams.enableLdm) {
            size_t error;
            assert(seqStore.seq != NULL && seqStore.pos == 0 &&
                   seqStore.size == 0 && seqStore.capacity > 0);
            assert(src.size <= serialState->params.jobSize);
            ZSTD_window_update(&serialState->ldmState.window, src.start, src.size);
            error = ZSTD_ldm_generateSequences(
                &serialState->ldmState, &seqStore,
                &serialState->params.ldmParams, src.start, src.size);
            /* We provide a large enough buffer to never fail. */
            assert(!ZSTD_isError(error)); (void)error;
            /* Update ldmWindow to match the ldmState.window and signal the main
             * thread if it is waiting for a buffer.
             */
            ZSTD_PTHREAD_MUTEX_LOCK(&serialState->ldmWindowMutex);
            serialState->ldmWindow = serialState->ldmState.window;
            ZSTD_pthread_cond_signal(&serialState->ldmWindowCond);
            ZSTD_pthread_mutex_unlock(&serialState->ldmWindowMutex);
        }
        if (serialState->params.fParams.checksumFlag && src.size > 0)
            XXH64_update(&serialState->xxhState, src.start, src.size);
    }
    /* Now it is the next jobs turn */
    serialState->nextJobID++;
    ZSTD_pthread_cond_broadcast(&serialState->cond);
    ZSTD_pthread_mutex_unlock(&serialState->mutex);

    if (seqStore.size > 0) {
        size_t const err = ZSTD_referenceExternalSequences(
            jobCCtx, seqStore.seq, seqStore.size);
        assert(serialState->params.ldmParams.enableLdm);
        assert(!ZSTD_isError(err));
        (void)err;
    }
}