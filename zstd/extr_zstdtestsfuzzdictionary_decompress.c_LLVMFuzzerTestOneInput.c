#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  void ZSTD_DDict ;
struct TYPE_3__ {void* buff; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ FUZZ_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (void*) ; 
 int /*<<< orphan*/  FUZZ_ZASSERT (int /*<<< orphan*/ ) ; 
 size_t FUZZ_rand32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FUZZ_seed (int /*<<< orphan*/  const**,size_t*) ; 
 TYPE_1__ FUZZ_train (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_DCtx_loadDictionary_advanced (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ZSTD_createDCtx () ; 
 void* ZSTD_createDDict (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_decompressDCtx (void*,void*,size_t const,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_decompress_usingDDict (void*,void*,size_t const,int /*<<< orphan*/  const*,size_t,void*) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (void*) ; 
 int /*<<< orphan*/  ZSTD_freeDDict (void*) ; 
 void* dctx ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t const) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    uint32_t seed = FUZZ_seed(&src, &size);
    FUZZ_dict_t dict;
    ZSTD_DDict* ddict = NULL;
    int i;

    if (!dctx) {
        dctx = ZSTD_createDCtx();
        FUZZ_ASSERT(dctx);
    }
    dict = FUZZ_train(src, size, &seed);
    if (FUZZ_rand32(&seed, 0, 1) == 0) {
        ddict = ZSTD_createDDict(dict.buff, dict.size);
        FUZZ_ASSERT(ddict);
    } else {
        FUZZ_ZASSERT(ZSTD_DCtx_loadDictionary_advanced(
                dctx, dict.buff, dict.size,
                (ZSTD_dictLoadMethod_e)FUZZ_rand32(&seed, 0, 1),
                (ZSTD_dictContentType_e)FUZZ_rand32(&seed, 0, 2)));
    }
    /* Run it 10 times over 10 output sizes. Reuse the context and dict. */
    for (i = 0; i < 10; ++i) {
        size_t const bufSize = FUZZ_rand32(&seed, 0, 2 * size);
        void* rBuf = malloc(bufSize);
        FUZZ_ASSERT(rBuf);
        if (ddict) {
            ZSTD_decompress_usingDDict(dctx, rBuf, bufSize, src, size, ddict);
        } else {
            ZSTD_decompressDCtx(dctx, rBuf, bufSize, src, size);
        }
        free(rBuf);
    }
    free(dict.buff);
    ZSTD_freeDDict(ddict);
#ifndef STATEFUL_FUZZING
    ZSTD_freeDCtx(dctx); dctx = NULL;
#endif
    return 0;
}