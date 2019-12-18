#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_7__ {unsigned int const totalBuffers; size_t bufferSize; int /*<<< orphan*/  cMem; } ;
typedef  TYPE_1__ ZSTDMT_bufferPool ;
typedef  int U32 ;

/* Variables and functions */
 TYPE_1__* ZSTDMT_createBufferPool (int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTDMT_freeBufferPool (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTDMT_setBufferSize (TYPE_1__*,size_t const) ; 

__attribute__((used)) static ZSTDMT_bufferPool* ZSTDMT_expandBufferPool(ZSTDMT_bufferPool* srcBufPool, U32 nbWorkers)
{
    unsigned const maxNbBuffers = 2*nbWorkers + 3;
    if (srcBufPool==NULL) return NULL;
    if (srcBufPool->totalBuffers >= maxNbBuffers) /* good enough */
        return srcBufPool;
    /* need a larger buffer pool */
    {   ZSTD_customMem const cMem = srcBufPool->cMem;
        size_t const bSize = srcBufPool->bufferSize;   /* forward parameters */
        ZSTDMT_bufferPool* newBufPool;
        ZSTDMT_freeBufferPool(srcBufPool);
        newBufPool = ZSTDMT_createBufferPool(nbWorkers, cMem);
        if (newBufPool==NULL) return newBufPool;
        ZSTDMT_setBufferSize(newBufPool, bSize);
        return newBufPool;
    }
}