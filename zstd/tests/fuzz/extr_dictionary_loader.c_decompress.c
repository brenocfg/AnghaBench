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
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ZASSERT (size_t const) ; 
 size_t const ZSTD_DCtx_loadDictionary_advanced (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 size_t ZSTD_decompressDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t decompress(void* result, size_t resultCapacity,
                         void const* compressed, size_t compressedSize,
                         void const* dict, size_t dictSize,
                       ZSTD_dictLoadMethod_e dictLoadMethod,
                         ZSTD_dictContentType_e dictContentType)
{
    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    FUZZ_ZASSERT(ZSTD_DCtx_loadDictionary_advanced(
            dctx, dict, dictSize, dictLoadMethod, dictContentType));
    size_t const resultSize = ZSTD_decompressDCtx(
            dctx, result, resultCapacity, compressed, compressedSize);
    FUZZ_ZASSERT(resultSize);
    ZSTD_freeDCtx(dctx);
    return resultSize;
}