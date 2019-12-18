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
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ZSTD_createCDict (void* const,size_t,int) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* mallocAndLoadFile_orDie (char const*,size_t*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static ZSTD_CDict* createCDict_orDie(const char* dictFileName, int cLevel)
{
    size_t dictSize;
    printf("loading dictionary %s \n", dictFileName);
    void* const dictBuffer = mallocAndLoadFile_orDie(dictFileName, &dictSize);
    ZSTD_CDict* const cdict = ZSTD_createCDict(dictBuffer, dictSize, cLevel);
    CHECK(cdict != NULL, "ZSTD_createCDict() failed!");
    free(dictBuffer);
    return cdict;
}