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
struct TYPE_3__ {int compressionLevel; unsigned int notificationLevel; unsigned int const dictID; } ;
typedef  TYPE_1__ ZDICT_params_t ;
typedef  unsigned int U64 ;
typedef  unsigned int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  MEM_writeLE32 (char*,unsigned int const) ; 
 size_t MIN (size_t,size_t) ; 
 unsigned int XXH64 (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t ZDICT_analyzeEntropy (char*,size_t,int const,void const*,size_t const*,unsigned int,char*,size_t,unsigned int const) ; 
 scalar_t__ ZDICT_isError (size_t const) ; 
 int /*<<< orphan*/  ZSTD_MAGIC_DICTIONARY ; 
 int g_compressionLevel_default ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

__attribute__((used)) static size_t ZDICT_addEntropyTablesFromBuffer_advanced(
        void* dictBuffer, size_t dictContentSize, size_t dictBufferCapacity,
        const void* samplesBuffer, const size_t* samplesSizes, unsigned nbSamples,
        ZDICT_params_t params)
{
    int const compressionLevel = (params.compressionLevel == 0) ? g_compressionLevel_default : params.compressionLevel;
    U32 const notificationLevel = params.notificationLevel;
    size_t hSize = 8;

    /* calculate entropy tables */
    DISPLAYLEVEL(2, "\r%70s\r", "");   /* clean display line */
    DISPLAYLEVEL(2, "statistics ... \n");
    {   size_t const eSize = ZDICT_analyzeEntropy((char*)dictBuffer+hSize, dictBufferCapacity-hSize,
                                  compressionLevel,
                                  samplesBuffer, samplesSizes, nbSamples,
                                  (char*)dictBuffer + dictBufferCapacity - dictContentSize, dictContentSize,
                                  notificationLevel);
        if (ZDICT_isError(eSize)) return eSize;
        hSize += eSize;
    }

    /* add dictionary header (after entropy tables) */
    MEM_writeLE32(dictBuffer, ZSTD_MAGIC_DICTIONARY);
    {   U64 const randomID = XXH64((char*)dictBuffer + dictBufferCapacity - dictContentSize, dictContentSize, 0);
        U32 const compliantID = (randomID % ((1U<<31)-32768)) + 32768;
        U32 const dictID = params.dictID ? params.dictID : compliantID;
        MEM_writeLE32((char*)dictBuffer+4, dictID);
    }

    if (hSize + dictContentSize < dictBufferCapacity)
        memmove((char*)dictBuffer + hSize, (char*)dictBuffer + dictBufferCapacity - dictContentSize, dictContentSize);
    return MIN(dictBufferCapacity, hSize+dictContentSize);
}