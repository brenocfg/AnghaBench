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
 int /*<<< orphan*/  CHECK_ZSTD (size_t const) ; 
 size_t ZSTD_compress (void* const,size_t const,void* const,size_t,int) ; 
 size_t ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* mallocAndLoadFile_orDie (char const*,size_t*) ; 
 void* malloc_orDie (size_t const) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  saveFile_orDie (char const*,void* const,size_t const) ; 

__attribute__((used)) static void compress_orDie(const char* fname, const char* oname)
{
    size_t fSize;
    void* const fBuff = mallocAndLoadFile_orDie(fname, &fSize);
    size_t const cBuffSize = ZSTD_compressBound(fSize);
    void* const cBuff = malloc_orDie(cBuffSize);

    /* Compress.
     * If you are doing many compressions, you may want to reuse the context.
     * See the multiple_simple_compression.c example.
     */
    size_t const cSize = ZSTD_compress(cBuff, cBuffSize, fBuff, fSize, 1);
    CHECK_ZSTD(cSize);

    saveFile_orDie(oname, cBuff, cSize);

    /* success */
    printf("%25s : %6u -> %7u - %s \n", fname, (unsigned)fSize, (unsigned)cSize, oname);

    free(fBuff);
    free(cBuff);
}