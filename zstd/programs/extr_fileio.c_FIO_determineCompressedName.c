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

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 char* FIO_createFilename_fromOutDir (char const*,char const*,size_t const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* strlen (char const*) ; 

__attribute__((used)) static const char*
FIO_determineCompressedName(const char* srcFileName, const char* outDirName, const char* suffix)
{
    static size_t dfnbCapacity = 0;
    static char* dstFileNameBuffer = NULL;   /* using static allocation : this function cannot be multi-threaded */
    char* outDirFilename = NULL;
    size_t sfnSize = strlen(srcFileName);
    size_t const srcSuffixLen = strlen(suffix);
    if (outDirName) {
        outDirFilename = FIO_createFilename_fromOutDir(srcFileName, outDirName, srcSuffixLen);
        sfnSize = strlen(outDirFilename);
        assert(outDirFilename != NULL);
    }

    if (dfnbCapacity <= sfnSize+srcSuffixLen+1) {
        /* resize buffer for dstName */
        free(dstFileNameBuffer);
        dfnbCapacity = sfnSize + srcSuffixLen + 30;
        dstFileNameBuffer = (char*)malloc(dfnbCapacity);
        if (!dstFileNameBuffer) {
            EXM_THROW(30, "zstd: %s", strerror(errno));
        }
    }
    assert(dstFileNameBuffer != NULL);

    if (outDirFilename) {
        memcpy(dstFileNameBuffer, outDirFilename, sfnSize);
        free(outDirFilename);
    } else {
        memcpy(dstFileNameBuffer, srcFileName, sfnSize);
    }
    memcpy(dstFileNameBuffer+sfnSize, suffix, srcSuffixLen+1 /* Include terminating null */);
    return dstFileNameBuffer;
}