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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,...) ; 
 int /*<<< orphan*/  CHECK_ZSTD (size_t const) ; 
 unsigned long long const ZSTD_CONTENTSIZE_ERROR ; 
 unsigned long long const ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 size_t ZSTD_decompress_usingDDict (int /*<<< orphan*/ * const,void* const,unsigned long long const,void* const,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ * const) ; 
 unsigned int ZSTD_getDictID_fromDDict (int /*<<< orphan*/  const*) ; 
 unsigned int ZSTD_getDictID_fromFrame (void* const,size_t) ; 
 unsigned long long ZSTD_getFrameContentSize (void* const,size_t) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* mallocAndLoadFile_orDie (char const*,size_t*) ; 
 void* malloc_orDie (size_t) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void decompress(const char* fname, const ZSTD_DDict* ddict)
{
    size_t cSize;
    void* const cBuff = mallocAndLoadFile_orDie(fname, &cSize);
    /* Read the content size from the frame header. For simplicity we require
     * that it is always present. By default, zstd will write the content size
     * in the header when it is known. If you can't guarantee that the frame
     * content size is always written into the header, either use streaming
     * decompression, or ZSTD_decompressBound().
     */
    unsigned long long const rSize = ZSTD_getFrameContentSize(cBuff, cSize);
    CHECK(rSize != ZSTD_CONTENTSIZE_ERROR, "%s: not compressed by zstd!", fname);
    CHECK(rSize != ZSTD_CONTENTSIZE_UNKNOWN, "%s: original size unknown!", fname);
    void* const rBuff = malloc_orDie((size_t)rSize);

    /* Check that the dictionary ID matches.
     * If a non-zstd dictionary is used, then both will be zero.
     * By default zstd always writes the dictionary ID into the frame.
     * Zstd will check if there is a dictionary ID mismatch as well.
     */
    unsigned const expectedDictID = ZSTD_getDictID_fromDDict(ddict);
    unsigned const actualDictID = ZSTD_getDictID_fromFrame(cBuff, cSize);
    CHECK(actualDictID == expectedDictID,
          "DictID mismatch: expected %u got %u",
          expectedDictID,
          actualDictID);

    /* Decompress using the dictionary.
     * If you need to control the decompression parameters, then use the
     * advanced API: ZSTD_DCtx_setParameter(), ZSTD_DCtx_refDDict(), and
     * ZSTD_decompressDCtx().
     */
    ZSTD_DCtx* const dctx = ZSTD_createDCtx();
    CHECK(dctx != NULL, "ZSTD_createDCtx() failed!");
    size_t const dSize = ZSTD_decompress_usingDDict(dctx, rBuff, rSize, cBuff, cSize, ddict);
    CHECK_ZSTD(dSize);
    /* When zstd knows the content size, it will error if it doesn't match. */
    CHECK(dSize == rSize, "Impossible because zstd will check this condition!");

    /* success */
    printf("%25s : %6u -> %7u \n", fname, (unsigned)cSize, (unsigned)rSize);

    ZSTD_freeDCtx(dctx);
    free(rBuff);
    free(cBuff);
}