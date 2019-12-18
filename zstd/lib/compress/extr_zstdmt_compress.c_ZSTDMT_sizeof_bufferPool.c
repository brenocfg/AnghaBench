#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer_t ;
struct TYPE_5__ {int totalBuffers; int /*<<< orphan*/  poolMutex; TYPE_1__* bTable; } ;
typedef  TYPE_2__ ZSTDMT_bufferPool ;
struct TYPE_4__ {scalar_t__ capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t ZSTDMT_sizeof_bufferPool(ZSTDMT_bufferPool* bufPool)
{
    size_t const poolSize = sizeof(*bufPool)
                          + (bufPool->totalBuffers - 1) * sizeof(buffer_t);
    unsigned u;
    size_t totalBufferSize = 0;
    ZSTD_pthread_mutex_lock(&bufPool->poolMutex);
    for (u=0; u<bufPool->totalBuffers; u++)
        totalBufferSize += bufPool->bTable[u].capacity;
    ZSTD_pthread_mutex_unlock(&bufPool->poolMutex);

    return poolSize + totalBufferSize;
}