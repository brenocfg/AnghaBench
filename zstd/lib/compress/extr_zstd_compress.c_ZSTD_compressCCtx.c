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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 size_t ZSTD_compress_usingDict (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

size_t ZSTD_compressCCtx(ZSTD_CCtx* cctx,
                         void* dst, size_t dstCapacity,
                   const void* src, size_t srcSize,
                         int compressionLevel)
{
    DEBUGLOG(4, "ZSTD_compressCCtx (srcSize=%u)", (unsigned)srcSize);
    assert(cctx != NULL);
    return ZSTD_compress_usingDict(cctx, dst, dstCapacity, src, srcSize, NULL, 0, compressionLevel);
}