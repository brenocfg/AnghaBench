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
typedef  int /*<<< orphan*/  HUFv07_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t HUFv07_decompress4X2_usingDTable_internal (void*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ HUFv07_isError (size_t const) ; 
 size_t HUFv07_readDTableX2 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t HUFv07_decompress4X2_DCtx (HUFv07_DTable* dctx, void* dst, size_t dstSize, const void* cSrc, size_t cSrcSize)
{
    const BYTE* ip = (const BYTE*) cSrc;

    size_t const hSize = HUFv07_readDTableX2 (dctx, cSrc, cSrcSize);
    if (HUFv07_isError(hSize)) return hSize;
    if (hSize >= cSrcSize) return ERROR(srcSize_wrong);
    ip += hSize; cSrcSize -= hSize;

    return HUFv07_decompress4X2_usingDTable_internal (dst, dstSize, ip, cSrcSize, dctx);
}