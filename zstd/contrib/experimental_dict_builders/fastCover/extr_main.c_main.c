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
typedef  int /*<<< orphan*/  sampleInfo ;
struct TYPE_4__ {int notificationLevel; unsigned int dictID; int /*<<< orphan*/  compressionLevel; } ;
typedef  TYPE_1__ ZDICT_params_t ;
struct TYPE_5__ {unsigned int k; unsigned int d; unsigned int f; unsigned int steps; unsigned int nbThreads; double splitPoint; TYPE_1__ zParams; } ;
typedef  TYPE_2__ ZDICT_fastCover_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CLEVEL ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int FASTCOVER_trainFromFiles (char const*,int /*<<< orphan*/ *,unsigned int,TYPE_2__*) ; 
 char** UTIL_createFileList (char const**,unsigned int,char**,unsigned int*,int) ; 
 int /*<<< orphan*/  UTIL_freeFileList (char const**,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  freeSampleInfo (int /*<<< orphan*/ *) ; 
 unsigned int g_defaultMaxDictSize ; 
 int /*<<< orphan*/ * getSampleInfo (char const**,unsigned int,size_t,unsigned int,int) ; 
 scalar_t__ longCommandWArg (char const**,char*) ; 
 scalar_t__ malloc (int) ; 
 unsigned int readU32FromChar (char const**) ; 

int main(int argCount, const char* argv[])
{
  int displayLevel = 2;
  const char* programName = argv[0];
  int operationResult = 0;

  /* Initialize arguments to default values */
  unsigned k = 0;
  unsigned d = 0;
  unsigned f = 23;
  unsigned steps = 32;
  unsigned nbThreads = 1;
  unsigned split = 100;
  const char* outputFile = "fastCoverDict";
  unsigned dictID = 0;
  unsigned maxDictSize = g_defaultMaxDictSize;

  /* Initialize table to store input files */
  const char** filenameTable = (const char**)malloc(argCount * sizeof(const char*));
  unsigned filenameIdx = 0;

  char* fileNamesBuf = NULL;
  unsigned fileNamesNb = filenameIdx;
  int followLinks = 0; /* follow directory recursively */
  const char** extendedFileList = NULL;

  /* Parse arguments */
  for (int i = 1; i < argCount; i++) {
    const char* argument = argv[i];
    if (longCommandWArg(&argument, "k=")) { k = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "d=")) { d = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "f=")) { f = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "steps=")) { steps = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "split=")) { split = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "dictID=")) { dictID = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "maxdict=")) { maxDictSize = readU32FromChar(&argument); continue; }
    if (longCommandWArg(&argument, "in=")) {
      filenameTable[filenameIdx] = argument;
      filenameIdx++;
      continue;
    }
    if (longCommandWArg(&argument, "out=")) {
      outputFile = argument;
      continue;
    }
    DISPLAYLEVEL(1, "Incorrect parameters\n");
    operationResult = 1;
    return operationResult;
  }

  /* Get the list of all files recursively (because followLinks==0)*/
  extendedFileList = UTIL_createFileList(filenameTable, filenameIdx, &fileNamesBuf,
                                        &fileNamesNb, followLinks);
  if (extendedFileList) {
      unsigned u;
      for (u=0; u<fileNamesNb; u++) DISPLAYLEVEL(4, "%u %s\n", u, extendedFileList[u]);
      free((void*)filenameTable);
      filenameTable = extendedFileList;
      filenameIdx = fileNamesNb;
  }

  size_t blockSize = 0;

  /* Set up zParams */
  ZDICT_params_t zParams;
  zParams.compressionLevel = DEFAULT_CLEVEL;
  zParams.notificationLevel = displayLevel;
  zParams.dictID = dictID;

  /* Set up fastCover params */
  ZDICT_fastCover_params_t params;
  params.zParams = zParams;
  params.k = k;
  params.d = d;
  params.f = f;
  params.steps = steps;
  params.nbThreads = nbThreads;
  params.splitPoint = (double)split/100;

  /* Build dictionary */
  sampleInfo* info = getSampleInfo(filenameTable,
                    filenameIdx, blockSize, maxDictSize, zParams.notificationLevel);
  operationResult = FASTCOVER_trainFromFiles(outputFile, info, maxDictSize, &params);

  /* Free allocated memory */
  UTIL_freeFileList(extendedFileList, fileNamesBuf);
  freeSampleInfo(info);

  return operationResult;
}