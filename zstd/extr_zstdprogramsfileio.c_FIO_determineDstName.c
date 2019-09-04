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
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,...) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 char* ZSTD_EXTENSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 scalar_t__ strcmp (char const* const,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* strlen (char const* const) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static const char*
FIO_determineDstName(const char* srcFileName)
{
    static size_t dfnbCapacity = 0;
    static char* dstFileNameBuffer = NULL;   /* using static allocation : this function cannot be multi-threaded */

    size_t const sfnSize = strlen(srcFileName);
    size_t suffixSize;
    const char* const suffixPtr = strrchr(srcFileName, '.');
    if (suffixPtr == NULL) {
        DISPLAYLEVEL(1, "zstd: %s: unknown suffix -- ignored \n",
                        srcFileName);
        return NULL;
    }
    suffixSize = strlen(suffixPtr);

    /* check suffix is authorized */
    if (sfnSize <= suffixSize
        || (   strcmp(suffixPtr, ZSTD_EXTENSION)
        #ifdef ZSTD_GZDECOMPRESS
            && strcmp(suffixPtr, GZ_EXTENSION)
        #endif
        #ifdef ZSTD_LZMADECOMPRESS
            && strcmp(suffixPtr, XZ_EXTENSION)
            && strcmp(suffixPtr, LZMA_EXTENSION)
        #endif
        #ifdef ZSTD_LZ4DECOMPRESS
            && strcmp(suffixPtr, LZ4_EXTENSION)
        #endif
            ) ) {
        const char* suffixlist = ZSTD_EXTENSION
        #ifdef ZSTD_GZDECOMPRESS
            "/" GZ_EXTENSION
        #endif
        #ifdef ZSTD_LZMADECOMPRESS
            "/" XZ_EXTENSION "/" LZMA_EXTENSION
        #endif
        #ifdef ZSTD_LZ4DECOMPRESS
            "/" LZ4_EXTENSION
        #endif
        ;
        DISPLAYLEVEL(1, "zstd: %s: unknown suffix (%s expected) -- ignored \n",
                     srcFileName, suffixlist);
        return NULL;
    }

    /* allocate enough space to write dstFilename into it */
    if (dfnbCapacity+suffixSize <= sfnSize+1) {
        free(dstFileNameBuffer);
        dfnbCapacity = sfnSize + 20;
        dstFileNameBuffer = (char*)malloc(dfnbCapacity);
        if (dstFileNameBuffer==NULL)
            EXM_THROW(74, "%s : not enough memory for dstFileName", strerror(errno));
    }

    /* return dst name == src name truncated from suffix */
    assert(dstFileNameBuffer != NULL);
    memcpy(dstFileNameBuffer, srcFileName, sfnSize - suffixSize);
    dstFileNameBuffer[sfnSize-suffixSize] = '\0';
    return dstFileNameBuffer;

    /* note : dstFileNameBuffer memory is not going to be free */
}