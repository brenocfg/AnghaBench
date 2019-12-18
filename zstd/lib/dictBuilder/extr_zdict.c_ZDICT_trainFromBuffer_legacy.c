#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZDICT_legacy_params_t ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ NOISELENGTH ; 
 size_t const ZDICT_MIN_SAMPLES_SIZE ; 
 int /*<<< orphan*/  ZDICT_fillNoise (char*,scalar_t__) ; 
 size_t ZDICT_totalSampleSize (size_t const*,unsigned int) ; 
 size_t ZDICT_trainFromBuffer_unsafe_legacy (void*,size_t,void*,size_t const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t const) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZDICT_trainFromBuffer_legacy(void* dictBuffer, size_t dictBufferCapacity,
                              const void* samplesBuffer, const size_t* samplesSizes, unsigned nbSamples,
                              ZDICT_legacy_params_t params)
{
    size_t result;
    void* newBuff;
    size_t const sBuffSize = ZDICT_totalSampleSize(samplesSizes, nbSamples);
    if (sBuffSize < ZDICT_MIN_SAMPLES_SIZE) return 0;   /* not enough content => no dictionary */

    newBuff = malloc(sBuffSize + NOISELENGTH);
    if (!newBuff) return ERROR(memory_allocation);

    memcpy(newBuff, samplesBuffer, sBuffSize);
    ZDICT_fillNoise((char*)newBuff + sBuffSize, NOISELENGTH);   /* guard band, for end of buffer condition */

    result =
        ZDICT_trainFromBuffer_unsafe_legacy(dictBuffer, dictBufferCapacity, newBuff,
                                            samplesSizes, nbSamples, params);
    free(newBuff);
    return result;
}