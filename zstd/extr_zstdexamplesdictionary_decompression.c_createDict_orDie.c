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
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ZSTD_createDDict (void* const,size_t) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* mallocAndLoadFile_orDie (char const*,size_t*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static ZSTD_DDict* createDict_orDie(const char* dictFileName)
{
    size_t dictSize;
    printf("loading dictionary %s \n", dictFileName);
    void* const dictBuffer = mallocAndLoadFile_orDie(dictFileName, &dictSize);
    ZSTD_DDict* const ddict = ZSTD_createDDict(dictBuffer, dictSize);
    CHECK(ddict != NULL, "ZSTD_createDDict() failed!");
    free(dictBuffer);
    return ddict;
}