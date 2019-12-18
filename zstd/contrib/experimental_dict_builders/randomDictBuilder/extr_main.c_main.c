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
struct TYPE_5__ {int notificationLevel; unsigned int dictID; int /*<<< orphan*/  compressionLevel; } ;
struct TYPE_4__ {unsigned int k; TYPE_2__ zParams; } ;
typedef  TYPE_1__ ZDICT_random_params_t ;
typedef  TYPE_2__ ZDICT_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CLEVEL ; 
 unsigned int DEFAULT_DICTID ; 
 char* DEFAULT_OUTPUTFILE ; 
 unsigned int DEFAULT_k ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int RANDOM_trainFromFiles (char const*,int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
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
  unsigned k = DEFAULT_k;
  const char* outputFile = DEFAULT_OUTPUTFILE;
  unsigned dictID = DEFAULT_DICTID;
  unsigned maxDictSize = g_defaultMaxDictSize;

  /* Initialize table to store input files */
  const char** filenameTable = (const char**)malloc(argCount * sizeof(const char*));
  unsigned filenameIdx = 0;

  /* Parse arguments */
  for (int i = 1; i < argCount; i++) {
    const char* argument = argv[i];
    if (longCommandWArg(&argument, "k=")) { k = readU32FromChar(&argument); continue; }
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

  char* fileNamesBuf = NULL;
  unsigned fileNamesNb = filenameIdx;
  int followLinks = 0; /* follow directory recursively */
  const char** extendedFileList = NULL;
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

  ZDICT_random_params_t params;
  ZDICT_params_t zParams;
  zParams.compressionLevel = DEFAULT_CLEVEL;
  zParams.notificationLevel = displayLevel;
  zParams.dictID = dictID;
  params.zParams = zParams;
  params.k = k;

  sampleInfo* info = getSampleInfo(filenameTable,
                    filenameIdx, blockSize, maxDictSize, zParams.notificationLevel);
  operationResult = RANDOM_trainFromFiles(outputFile, info, maxDictSize, &params);

  /* Free allocated memory */
  UTIL_freeFileList(extendedFileList, fileNamesBuf);
  freeSampleInfo(info);

  return operationResult;
}