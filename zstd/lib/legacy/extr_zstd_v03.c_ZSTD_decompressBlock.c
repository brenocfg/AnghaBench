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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ZSTD_decodeLiteralsBlock (void*,void const*,size_t) ; 
 size_t ZSTD_decompressSequences (void*,void*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 

__attribute__((used)) static size_t ZSTD_decompressBlock(
                            void* ctx,
                            void* dst, size_t maxDstSize,
                      const void* src, size_t srcSize)
{
    /* blockType == blockCompressed */
    const BYTE* ip = (const BYTE*)src;

    /* Decode literals sub-block */
    size_t litCSize = ZSTD_decodeLiteralsBlock(ctx, src, srcSize);
    if (ZSTD_isError(litCSize)) return litCSize;
    ip += litCSize;
    srcSize -= litCSize;

    return ZSTD_decompressSequences(ctx, dst, maxDstSize, ip, srcSize);
}