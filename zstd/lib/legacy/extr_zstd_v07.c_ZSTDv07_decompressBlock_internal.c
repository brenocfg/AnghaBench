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
typedef  int /*<<< orphan*/  ZSTDv07_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDv07_BLOCKSIZE_ABSOLUTEMAX ; 
 size_t ZSTDv07_decodeLiteralsBlock (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTDv07_decompressSequences (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ ZSTDv07_isError (size_t const) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv07_decompressBlock_internal(ZSTDv07_DCtx* dctx,
                            void* dst, size_t dstCapacity,
                      const void* src, size_t srcSize)
{   /* blockType == blockCompressed */
    const BYTE* ip = (const BYTE*)src;

    if (srcSize >= ZSTDv07_BLOCKSIZE_ABSOLUTEMAX) return ERROR(srcSize_wrong);

    /* Decode literals sub-block */
    {   size_t const litCSize = ZSTDv07_decodeLiteralsBlock(dctx, src, srcSize);
        if (ZSTDv07_isError(litCSize)) return litCSize;
        ip += litCSize;
        srcSize -= litCSize;
    }
    return ZSTDv07_decompressSequences(dctx, dst, dstCapacity, ip, srcSize);
}