#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int nbSamples; size_t const totalSizeToLoad; scalar_t__ oneSampleTooLarge; } ;
typedef  TYPE_4__ fileStats ;
struct TYPE_17__ {unsigned int notificationLevel; } ;
struct TYPE_21__ {TYPE_1__ zParams; } ;
typedef  TYPE_5__ ZDICT_legacy_params_t ;
struct TYPE_19__ {unsigned int notificationLevel; } ;
struct TYPE_22__ {int splitPoint; int /*<<< orphan*/  accel; int /*<<< orphan*/  steps; int /*<<< orphan*/  f; int /*<<< orphan*/  d; int /*<<< orphan*/  k; TYPE_3__ zParams; } ;
typedef  TYPE_6__ ZDICT_fastCover_params_t ;
struct TYPE_18__ {unsigned int notificationLevel; } ;
struct TYPE_23__ {int splitPoint; int /*<<< orphan*/  steps; int /*<<< orphan*/  d; int /*<<< orphan*/  k; TYPE_2__ zParams; } ;
typedef  TYPE_7__ ZDICT_cover_params_t ;

/* Variables and functions */
 size_t COVER_MEMMULT ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 TYPE_4__ DiB_fileStats (char const**,unsigned int,size_t,unsigned int const) ; 
 int /*<<< orphan*/  DiB_fillNoise (char*,size_t) ; 
 size_t const DiB_findMaxMem (size_t const) ; 
 int /*<<< orphan*/  DiB_loadFiles (void* const,size_t*,size_t* const,int,char const**,unsigned int,size_t,unsigned int const) ; 
 int /*<<< orphan*/  DiB_saveDict (char const*,void* const,size_t) ; 
 int /*<<< orphan*/  DiB_shuffle (char const**,unsigned int) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 size_t FASTCOVER_MEMMULT ; 
 size_t MEMMULT ; 
 int /*<<< orphan*/  MIN (unsigned long long,size_t const) ; 
 size_t NOISELENGTH ; 
 int /*<<< orphan*/  SAMPLESIZE_MAX ; 
 int /*<<< orphan*/  ZDICT_getErrorName (size_t) ; 
 scalar_t__ ZDICT_isError (size_t) ; 
 size_t ZDICT_optimizeTrainFromBuffer_cover (void* const,unsigned int,void* const,size_t* const,int,TYPE_7__*) ; 
 size_t ZDICT_optimizeTrainFromBuffer_fastCover (void* const,unsigned int,void* const,size_t* const,int,TYPE_6__*) ; 
 size_t ZDICT_trainFromBuffer_cover (void* const,unsigned int,void* const,size_t* const,int,TYPE_7__) ; 
 size_t ZDICT_trainFromBuffer_fastCover (void* const,unsigned int,void* const,size_t* const,int,TYPE_6__) ; 
 size_t ZDICT_trainFromBuffer_unsafe_legacy (void* const,unsigned int,void* const,size_t* const,int,TYPE_5__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t) ; 

int DiB_trainFromFiles(const char* dictFileName, unsigned maxDictSize,
                       const char** fileNamesTable, unsigned nbFiles, size_t chunkSize,
                       ZDICT_legacy_params_t* params, ZDICT_cover_params_t* coverParams,
                       ZDICT_fastCover_params_t* fastCoverParams, int optimize)
{
    unsigned const displayLevel = params ? params->zParams.notificationLevel :
                        coverParams ? coverParams->zParams.notificationLevel :
                        fastCoverParams ? fastCoverParams->zParams.notificationLevel :
                        0;   /* should never happen */
    void* const dictBuffer = malloc(maxDictSize);
    fileStats const fs = DiB_fileStats(fileNamesTable, nbFiles, chunkSize, displayLevel);
    size_t* const sampleSizes = (size_t*)malloc(fs.nbSamples * sizeof(size_t));
    size_t const memMult = params ? MEMMULT :
                           coverParams ? COVER_MEMMULT:
                           FASTCOVER_MEMMULT;
    size_t const maxMem =  DiB_findMaxMem(fs.totalSizeToLoad * memMult) / memMult;
    size_t loadedSize = (size_t) MIN ((unsigned long long)maxMem, fs.totalSizeToLoad);
    void* const srcBuffer = malloc(loadedSize+NOISELENGTH);
    int result = 0;

    /* Checks */
    if ((!sampleSizes) || (!srcBuffer) || (!dictBuffer))
        EXM_THROW(12, "not enough memory for DiB_trainFiles");   /* should not happen */
    if (fs.oneSampleTooLarge) {
        DISPLAYLEVEL(2, "!  Warning : some sample(s) are very large \n");
        DISPLAYLEVEL(2, "!  Note that dictionary is only useful for small samples. \n");
        DISPLAYLEVEL(2, "!  As a consequence, only the first %u bytes of each sample are loaded \n", SAMPLESIZE_MAX);
    }
    if (fs.nbSamples < 5) {
        DISPLAYLEVEL(2, "!  Warning : nb of samples too low for proper processing ! \n");
        DISPLAYLEVEL(2, "!  Please provide _one file per sample_. \n");
        DISPLAYLEVEL(2, "!  Alternatively, split files into fixed-size blocks representative of samples, with -B# \n");
        EXM_THROW(14, "nb of samples too low");   /* we now clearly forbid this case */
    }
    if (fs.totalSizeToLoad < (unsigned long long)(8 * maxDictSize)) {
        DISPLAYLEVEL(2, "!  Warning : data size of samples too small for target dictionary size \n");
        DISPLAYLEVEL(2, "!  Samples should be about 100x larger than target dictionary size \n");
    }

    /* init */
    if (loadedSize < fs.totalSizeToLoad)
        DISPLAYLEVEL(1, "Not enough memory; training on %u MB only...\n", (unsigned)(loadedSize >> 20));

    /* Load input buffer */
    DISPLAYLEVEL(3, "Shuffling input files\n");
    DiB_shuffle(fileNamesTable, nbFiles);

    DiB_loadFiles(srcBuffer, &loadedSize, sampleSizes, fs.nbSamples, fileNamesTable, nbFiles, chunkSize, displayLevel);

    {   size_t dictSize;
        if (params) {
            DiB_fillNoise((char*)srcBuffer + loadedSize, NOISELENGTH);   /* guard band, for end of buffer condition */
            dictSize = ZDICT_trainFromBuffer_unsafe_legacy(dictBuffer, maxDictSize,
                                                           srcBuffer, sampleSizes, fs.nbSamples,
                                                           *params);
        } else if (coverParams) {
            if (optimize) {
              dictSize = ZDICT_optimizeTrainFromBuffer_cover(dictBuffer, maxDictSize,
                                                             srcBuffer, sampleSizes, fs.nbSamples,
                                                             coverParams);
              if (!ZDICT_isError(dictSize)) {
                  unsigned splitPercentage = (unsigned)(coverParams->splitPoint * 100);
                  DISPLAYLEVEL(2, "k=%u\nd=%u\nsteps=%u\nsplit=%u\n", coverParams->k, coverParams->d,
                              coverParams->steps, splitPercentage);
              }
            } else {
              dictSize = ZDICT_trainFromBuffer_cover(dictBuffer, maxDictSize, srcBuffer,
                                                     sampleSizes, fs.nbSamples, *coverParams);
            }
        } else {
            assert(fastCoverParams != NULL);
            if (optimize) {
              dictSize = ZDICT_optimizeTrainFromBuffer_fastCover(dictBuffer, maxDictSize,
                                                              srcBuffer, sampleSizes, fs.nbSamples,
                                                              fastCoverParams);
              if (!ZDICT_isError(dictSize)) {
                unsigned splitPercentage = (unsigned)(fastCoverParams->splitPoint * 100);
                DISPLAYLEVEL(2, "k=%u\nd=%u\nf=%u\nsteps=%u\nsplit=%u\naccel=%u\n", fastCoverParams->k,
                            fastCoverParams->d, fastCoverParams->f, fastCoverParams->steps, splitPercentage,
                            fastCoverParams->accel);
              }
            } else {
              dictSize = ZDICT_trainFromBuffer_fastCover(dictBuffer, maxDictSize, srcBuffer,
                                                        sampleSizes, fs.nbSamples, *fastCoverParams);
            }
        }
        if (ZDICT_isError(dictSize)) {
            DISPLAYLEVEL(1, "dictionary training failed : %s \n", ZDICT_getErrorName(dictSize));   /* should not happen */
            result = 1;
            goto _cleanup;
        }
        /* save dict */
        DISPLAYLEVEL(2, "Save dictionary of size %u into file %s \n", (unsigned)dictSize, dictFileName);
        DiB_saveDict(dictFileName, dictBuffer, dictSize);
    }

    /* clean up */
_cleanup:
    free(srcBuffer);
    free(sampleSizes);
    free(dictBuffer);
    return result;
}