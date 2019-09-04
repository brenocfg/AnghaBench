#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * start; scalar_t__ capacity; } ;
typedef  TYPE_1__ buffer_t ;
struct TYPE_6__ {int nbBuffers; int totalBuffers; int /*<<< orphan*/  cMem; int /*<<< orphan*/  poolMutex; TYPE_1__* bTable; } ;
typedef  TYPE_2__ ZSTDMT_bufferPool ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int /*<<< orphan*/  ZSTD_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_releaseBuffer(ZSTDMT_bufferPool* bufPool, buffer_t buf)
{
    DEBUGLOG(5, "ZSTDMT_releaseBuffer");
    if (buf.start == NULL) return;   /* compatible with release on NULL */
    ZSTD_pthread_mutex_lock(&bufPool->poolMutex);
    if (bufPool->nbBuffers < bufPool->totalBuffers) {
        bufPool->bTable[bufPool->nbBuffers++] = buf;  /* stored for later use */
        DEBUGLOG(5, "ZSTDMT_releaseBuffer: stored buffer of size %u in slot %u",
                    (U32)buf.capacity, (U32)(bufPool->nbBuffers-1));
        ZSTD_pthread_mutex_unlock(&bufPool->poolMutex);
        return;
    }
    ZSTD_pthread_mutex_unlock(&bufPool->poolMutex);
    /* Reached bufferPool capacity (should not happen) */
    DEBUGLOG(5, "ZSTDMT_releaseBuffer: pool capacity reached => freeing ");
    ZSTD_free(buf.start, bufPool->cMem);
}