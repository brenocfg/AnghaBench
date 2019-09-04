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
struct TYPE_5__ {int nbSamples; size_t* samplesSizes; void* srcBuffer; } ;
typedef  TYPE_1__ sampleInfo ;
struct TYPE_6__ {int nbSamples; size_t const totalSizeToLoad; scalar_t__ oneSampleTooLarge; } ;
typedef  TYPE_2__ fileStats ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/  MIN (unsigned long long,size_t const) ; 
 size_t NOISELENGTH ; 
 size_t RANDOM_MEMMULT ; 
 int /*<<< orphan*/  SAMPLESIZE_MAX ; 
 size_t const findMaxMem (size_t const) ; 
 TYPE_2__ getFileStats (char const**,unsigned int,size_t,unsigned int const) ; 
 unsigned int loadFiles (void* const,size_t*,size_t* const,int,char const**,unsigned int,size_t,unsigned int const) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  shuffle (char const**,unsigned int) ; 

sampleInfo* getSampleInfo(const char** fileNamesTable, unsigned nbFiles, size_t chunkSize,
                          unsigned maxDictSize, const unsigned displayLevel) {
    fileStats const fs = getFileStats(fileNamesTable, nbFiles, chunkSize, displayLevel);
    size_t* const sampleSizes = (size_t*)malloc(fs.nbSamples * sizeof(size_t));
    size_t const memMult = RANDOM_MEMMULT;
    size_t const maxMem =  findMaxMem(fs.totalSizeToLoad * memMult) / memMult;
    size_t loadedSize = (size_t) MIN ((unsigned long long)maxMem, fs.totalSizeToLoad);
    void* const srcBuffer = malloc(loadedSize+NOISELENGTH);

    /* Checks */
    if ((!sampleSizes) || (!srcBuffer))
        EXM_THROW(12, "not enough memory for trainFromFiles");   /* should not happen */
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
    shuffle(fileNamesTable, nbFiles);
    nbFiles = loadFiles(srcBuffer, &loadedSize, sampleSizes, fs.nbSamples,
                        fileNamesTable, nbFiles, chunkSize, displayLevel);

    sampleInfo *info = (sampleInfo *)malloc(sizeof(sampleInfo));

    info->nbSamples = fs.nbSamples;
    info->samplesSizes = sampleSizes;
    info->srcBuffer = srcBuffer;

    return info;
}