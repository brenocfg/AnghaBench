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
struct TYPE_8__ {int /*<<< orphan*/  nbSamples; int /*<<< orphan*/  samplesSizes; int /*<<< orphan*/  srcBuffer; } ;
typedef  TYPE_2__ sampleInfo ;
struct TYPE_7__ {unsigned int notificationLevel; } ;
struct TYPE_9__ {int /*<<< orphan*/  k; TYPE_1__ zParams; } ;
typedef  TYPE_3__ ZDICT_random_params_t ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/  ZDICT_getErrorName (size_t) ; 
 scalar_t__ ZDICT_isError (size_t) ; 
 size_t ZDICT_trainFromBuffer_random (void* const,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (unsigned int) ; 
 int /*<<< orphan*/  saveDict (char const*,void* const,size_t) ; 

int RANDOM_trainFromFiles(const char* dictFileName, sampleInfo *info,
                          unsigned maxDictSize,
                          ZDICT_random_params_t *params) {
    unsigned const displayLevel = params->zParams.notificationLevel;
    void* const dictBuffer = malloc(maxDictSize);

    int result = 0;

    /* Checks */
    if (!dictBuffer)
        EXM_THROW(12, "not enough memory for trainFromFiles");   /* should not happen */

    {   size_t dictSize;
        dictSize = ZDICT_trainFromBuffer_random(dictBuffer, maxDictSize, info->srcBuffer,
                                             info->samplesSizes, info->nbSamples, *params);
        DISPLAYLEVEL(2, "k=%u\n", params->k);
        if (ZDICT_isError(dictSize)) {
            DISPLAYLEVEL(1, "dictionary training failed : %s \n", ZDICT_getErrorName(dictSize));   /* should not happen */
            result = 1;
            goto _done;
        }
        /* save dict */
        DISPLAYLEVEL(2, "Save dictionary of size %u into file %s \n", (U32)dictSize, dictFileName);
        saveDict(dictFileName, dictBuffer, dictSize);
    }

    /* clean up */
_done:
    free(dictBuffer);
    return result;
}