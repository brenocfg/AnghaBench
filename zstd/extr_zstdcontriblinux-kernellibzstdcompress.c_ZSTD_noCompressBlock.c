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
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_blockHeaderSize ; 
 int /*<<< orphan*/  ZSTD_writeLE24 (void*,scalar_t__) ; 
 scalar_t__ bt_raw ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

size_t ZSTD_noCompressBlock(void *dst, size_t dstCapacity, const void *src, size_t srcSize)
{
	if (srcSize + ZSTD_blockHeaderSize > dstCapacity)
		return ERROR(dstSize_tooSmall);
	memcpy((BYTE *)dst + ZSTD_blockHeaderSize, src, srcSize);
	ZSTD_writeLE24(dst, (U32)(srcSize << 2) + (U32)bt_raw);
	return ZSTD_blockHeaderSize + srcSize;
}