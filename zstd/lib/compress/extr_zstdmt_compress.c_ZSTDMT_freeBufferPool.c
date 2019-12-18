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
struct TYPE_6__ {unsigned int totalBuffers; int /*<<< orphan*/  cMem; int /*<<< orphan*/  poolMutex; TYPE_1__* bTable; } ;
typedef  TYPE_2__ ZSTDMT_bufferPool ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {TYPE_2__* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_freeBufferPool(ZSTDMT_bufferPool* bufPool)
{
    unsigned u;
    DEBUGLOG(3, "ZSTDMT_freeBufferPool (address:%08X)", (U32)(size_t)bufPool);
    if (!bufPool) return;   /* compatibility with free on NULL */
    for (u=0; u<bufPool->totalBuffers; u++) {
        DEBUGLOG(4, "free buffer %2u (address:%08X)", u, (U32)(size_t)bufPool->bTable[u].start);
        ZSTD_free(bufPool->bTable[u].start, bufPool->cMem);
    }
    ZSTD_pthread_mutex_destroy(&bufPool->poolMutex);
    ZSTD_free(bufPool, bufPool->cMem);
}