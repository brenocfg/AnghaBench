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
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_writeLE24 (void*,int const) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 size_t ZSTD_blockHeaderSize ; 
 scalar_t__ bt_raw ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static size_t ZSTD_noCompressBlock (void* dst, size_t dstCapacity, const void* src, size_t srcSize, U32 lastBlock)
{
    U32 const cBlockHeader24 = lastBlock + (((U32)bt_raw)<<1) + (U32)(srcSize << 3);
    RETURN_ERROR_IF(srcSize + ZSTD_blockHeaderSize > dstCapacity,
                    dstSize_tooSmall);
    MEM_writeLE24(dst, cBlockHeader24);
    memcpy((BYTE*)dst + ZSTD_blockHeaderSize, src, srcSize);
    return ZSTD_blockHeaderSize + srcSize;
}