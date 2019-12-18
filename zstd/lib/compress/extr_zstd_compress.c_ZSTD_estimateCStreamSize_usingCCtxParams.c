#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t windowLog; } ;
typedef  TYPE_1__ ZSTD_compressionParameters ;
struct TYPE_8__ {scalar_t__ nbWorkers; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 int ZSTD_compressBound (size_t const) ; 
 size_t ZSTD_cwksp_alloc_size (size_t const) ; 
 size_t ZSTD_estimateCCtxSize_usingCCtxParams (TYPE_2__ const*) ; 
 TYPE_1__ ZSTD_getCParamsFromCCtxParams (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t ZSTD_estimateCStreamSize_usingCCtxParams(const ZSTD_CCtx_params* params)
{
    RETURN_ERROR_IF(params->nbWorkers > 0, GENERIC, "Estimate CCtx size is supported for single-threaded compression only.");
    {   ZSTD_compressionParameters const cParams =
                ZSTD_getCParamsFromCCtxParams(params, ZSTD_CONTENTSIZE_UNKNOWN, 0);
        size_t const CCtxSize = ZSTD_estimateCCtxSize_usingCCtxParams(params);
        size_t const blockSize = MIN(ZSTD_BLOCKSIZE_MAX, (size_t)1 << cParams.windowLog);
        size_t const inBuffSize = ((size_t)1 << cParams.windowLog) + blockSize;
        size_t const outBuffSize = ZSTD_compressBound(blockSize) + 1;
        size_t const streamingSize = ZSTD_cwksp_alloc_size(inBuffSize)
                                   + ZSTD_cwksp_alloc_size(outBuffSize);

        return CCtxSize + streamingSize;
    }
}