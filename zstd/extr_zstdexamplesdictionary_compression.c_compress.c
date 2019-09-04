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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHECK_ZSTD (size_t const) ; 
 size_t ZSTD_compressBound (size_t) ; 
 size_t ZSTD_compress_usingCDict (int /*<<< orphan*/ * const,void* const,size_t const,void* const,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* mallocAndLoadFile_orDie (char const*,size_t*) ; 
 void* malloc_orDie (size_t const) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  saveFile_orDie (char const*,void* const,size_t const) ; 

__attribute__((used)) static void compress(const char* fname, const char* oname, const ZSTD_CDict* cdict)
{
    size_t fSize;
    void* const fBuff = mallocAndLoadFile_orDie(fname, &fSize);
    size_t const cBuffSize = ZSTD_compressBound(fSize);
    void* const cBuff = malloc_orDie(cBuffSize);

    /* Compress using the dictionary.
     * This function writes the dictionary id, and content size into the header.
     * But, it doesn't use a checksum. You can control these options using the
     * advanced API: ZSTD_CCtx_setParameter(), ZSTD_CCtx_refCDict(),
     * and ZSTD_compress2().
     */
    ZSTD_CCtx* const cctx = ZSTD_createCCtx();
    CHECK(cctx != NULL, "ZSTD_createCCtx() failed!");
    size_t const cSize = ZSTD_compress_usingCDict(cctx, cBuff, cBuffSize, fBuff, fSize, cdict);
    CHECK_ZSTD(cSize);

    saveFile_orDie(oname, cBuff, cSize);

    /* success */
    printf("%25s : %6u -> %7u - %s \n", fname, (unsigned)fSize, (unsigned)cSize, oname);

    ZSTD_freeCCtx(cctx);   /* never fails */
    free(fBuff);
    free(cBuff);
}