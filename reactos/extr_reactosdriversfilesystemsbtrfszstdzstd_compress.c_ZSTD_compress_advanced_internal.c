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
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_compressBegin_internal (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_dtlm_fast ; 
 int /*<<< orphan*/  ZSTDb_not_buffered ; 

size_t ZSTD_compress_advanced_internal(
        ZSTD_CCtx* cctx,
        void* dst, size_t dstCapacity,
        const void* src, size_t srcSize,
        const void* dict,size_t dictSize,
        ZSTD_CCtx_params params)
{
    DEBUGLOG(4, "ZSTD_compress_advanced_internal (srcSize:%u)", (U32)srcSize);
    CHECK_F( ZSTD_compressBegin_internal(cctx,
                         dict, dictSize, ZSTD_dct_auto, ZSTD_dtlm_fast, NULL,
                         params, srcSize, ZSTDb_not_buffered) );
    return ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
}