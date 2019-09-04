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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (void*) ; 
 size_t FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FUZZ_seed (int /*<<< orphan*/  const**,size_t*) ; 
 void* ZSTD_createDCtx () ; 
 int /*<<< orphan*/  ZSTD_decompressDCtx (void*,void*,size_t const,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (void*) ; 
 void* dctx ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t const) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{

    uint32_t seed = FUZZ_seed(&src, &size);
    int i;
    if (!dctx) {
        dctx = ZSTD_createDCtx();
        FUZZ_ASSERT(dctx);
    }
    /* Run it 10 times over 10 output sizes. Reuse the context. */
    for (i = 0; i < 10; ++i) {
        size_t const bufSize = FUZZ_rand32(&seed, 0, 2 * size);
        void* rBuf = malloc(bufSize);
        FUZZ_ASSERT(rBuf);
        ZSTD_decompressDCtx(dctx, rBuf, bufSize, src, size);
        free(rBuf);
    }

#ifndef STATEFUL_FUZZING
    ZSTD_freeDCtx(dctx); dctx = NULL;
#endif
    return 0;
}