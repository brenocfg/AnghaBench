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
struct TYPE_3__ {unsigned int nextJobID; int /*<<< orphan*/  mutex; int /*<<< orphan*/  ldmWindowMutex; int /*<<< orphan*/  ldmWindowCond; int /*<<< orphan*/  ldmWindow; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ serialState_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int /*<<< orphan*/  ZSTD_PTHREAD_MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_window_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ZSTDMT_serialState_ensureFinished(serialState_t* serialState,
                                              unsigned jobID, size_t cSize)
{
    ZSTD_PTHREAD_MUTEX_LOCK(&serialState->mutex);
    if (serialState->nextJobID <= jobID) {
        assert(ZSTD_isError(cSize)); (void)cSize;
        DEBUGLOG(5, "Skipping past job %u because of error", jobID);
        serialState->nextJobID = jobID + 1;
        ZSTD_pthread_cond_broadcast(&serialState->cond);

        ZSTD_PTHREAD_MUTEX_LOCK(&serialState->ldmWindowMutex);
        ZSTD_window_clear(&serialState->ldmWindow);
        ZSTD_pthread_cond_signal(&serialState->ldmWindowCond);
        ZSTD_pthread_mutex_unlock(&serialState->ldmWindowMutex);
    }
    ZSTD_pthread_mutex_unlock(&serialState->mutex);

}