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
typedef  int /*<<< orphan*/  ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compressBegin_usingCDict_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

size_t ZSTD_compress_usingCDict_advanced(ZSTD_CCtx* cctx,
                                void* dst, size_t dstCapacity,
                                const void* src, size_t srcSize,
                                const ZSTD_CDict* cdict, ZSTD_frameParameters fParams)
{
    FORWARD_IF_ERROR(ZSTD_compressBegin_usingCDict_advanced(cctx, cdict, fParams, srcSize));   /* will check if cdict != NULL */
    return ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
}