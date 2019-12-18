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
typedef  int /*<<< orphan*/  ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZBUFF_CCtx ;

/* Variables and functions */
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_initCStream_advanced (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,unsigned long long) ; 

size_t ZBUFF_compressInit_advanced(ZBUFF_CCtx* zbc,
                                   const void* dict, size_t dictSize,
                                   ZSTD_parameters params, unsigned long long pledgedSrcSize)
{
    if (pledgedSrcSize==0) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;  /* preserve "0 == unknown" behavior */
    return ZSTD_initCStream_advanced(zbc, dict, dictSize, params, pledgedSrcSize);
}