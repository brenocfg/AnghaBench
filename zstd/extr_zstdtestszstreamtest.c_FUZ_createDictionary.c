#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; size_t filled; scalar_t__ start; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZ_freeDictionary (TYPE_1__) ; 
 scalar_t__ ZDICT_isError (size_t const) ; 
 size_t ZDICT_trainFromBuffer (scalar_t__,size_t,void const*,size_t* const,unsigned int) ; 
 int /*<<< orphan*/  free (size_t* const) ; 
 TYPE_1__ kBuffNull ; 
 scalar_t__ malloc (size_t const) ; 

__attribute__((used)) static buffer_t FUZ_createDictionary(const void* src, size_t srcSize, size_t blockSize, size_t requestedDictSize)
{
    buffer_t dict = kBuffNull;
    size_t const nbBlocks = (srcSize + (blockSize-1)) / blockSize;
    size_t* const blockSizes = (size_t*)malloc(nbBlocks * sizeof(size_t));
    if (!blockSizes) return kBuffNull;
    dict.start = malloc(requestedDictSize);
    if (!dict.start) { free(blockSizes); return kBuffNull; }
    {   size_t nb;
        for (nb=0; nb<nbBlocks-1; nb++) blockSizes[nb] = blockSize;
        blockSizes[nbBlocks-1] = srcSize - (blockSize * (nbBlocks-1));
    }
    {   size_t const dictSize = ZDICT_trainFromBuffer(dict.start, requestedDictSize, src, blockSizes, (unsigned)nbBlocks);
        free(blockSizes);
        if (ZDICT_isError(dictSize)) { FUZ_freeDictionary(dict); return kBuffNull; }
        dict.size = requestedDictSize;
        dict.filled = dictSize;
        return dict;
    }
}