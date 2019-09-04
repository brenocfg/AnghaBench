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
 int /*<<< orphan*/  FUZZ_ZASSERT (size_t) ; 
 int FUZZ_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUZZ_setRandomParameters (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 size_t ZSTD_compress2 (int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 
 size_t ZSTD_compressCCtx (int /*<<< orphan*/ ,void*,size_t,void const*,size_t,int const) ; 
 size_t ZSTD_decompressDCtx (int /*<<< orphan*/ ,void*,size_t,void*,size_t) ; 
 int /*<<< orphan*/  cctx ; 
 int /*<<< orphan*/  dctx ; 
 int kMaxClevel ; 
 int /*<<< orphan*/  seed ; 

__attribute__((used)) static size_t roundTripTest(void *result, size_t resultCapacity,
                            void *compressed, size_t compressedCapacity,
                            const void *src, size_t srcSize)
{
    size_t cSize;
    if (FUZZ_rand(&seed) & 1) {
        FUZZ_setRandomParameters(cctx, srcSize, &seed);
        cSize = ZSTD_compress2(cctx, compressed, compressedCapacity, src, srcSize);
    } else {
        int const cLevel = FUZZ_rand(&seed) % kMaxClevel;
        cSize = ZSTD_compressCCtx(
            cctx, compressed, compressedCapacity, src, srcSize, cLevel);
    }
    FUZZ_ZASSERT(cSize);
    return ZSTD_decompressDCtx(dctx, result, resultCapacity, compressed, cSize);
}