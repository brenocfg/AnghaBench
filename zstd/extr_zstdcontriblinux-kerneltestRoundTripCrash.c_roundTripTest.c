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
typedef  int /*<<< orphan*/  ZSTD_parameters ;

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ ,void*,size_t,void const*,size_t,int /*<<< orphan*/  const) ; 
 size_t ZSTD_decompressDCtx (int /*<<< orphan*/ ,void*,size_t,void*,size_t const) ; 
 int ZSTD_getErrorCode (size_t const) ; 
 int /*<<< orphan*/  ZSTD_getParams (int const,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  cctx ; 
 int /*<<< orphan*/  dctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int const kMaxClevel ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int xxh32 (void const*,size_t const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t roundTripTest(void* resultBuff, size_t resultBuffCapacity,
                            void* compressedBuff, size_t compressedBuffCapacity,
                      const void* srcBuff, size_t srcBuffSize)
{
    size_t const hashLength = MIN(128, srcBuffSize);
    unsigned const h32 = xxh32(srcBuff, hashLength, 0);
    int const cLevel = h32 % kMaxClevel;
    ZSTD_parameters const params = ZSTD_getParams(cLevel, srcBuffSize, 0);
    size_t const cSize = ZSTD_compressCCtx(cctx, compressedBuff, compressedBuffCapacity, srcBuff, srcBuffSize, params);
    if (ZSTD_isError(cSize)) {
        fprintf(stderr, "Compression error : %u \n", ZSTD_getErrorCode(cSize));
        return cSize;
    }
    return ZSTD_decompressDCtx(dctx, resultBuff, resultBuffCapacity, compressedBuff, cSize);
}