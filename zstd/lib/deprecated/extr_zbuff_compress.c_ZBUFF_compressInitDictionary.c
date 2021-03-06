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
typedef  int /*<<< orphan*/  ZBUFF_CCtx ;

/* Variables and functions */
 size_t ZSTD_initCStream_usingDict (int /*<<< orphan*/ *,void const*,size_t,int) ; 

size_t ZBUFF_compressInitDictionary(ZBUFF_CCtx* zbc, const void* dict, size_t dictSize, int compressionLevel)
{
    return ZSTD_initCStream_usingDict(zbc, dict, dictSize, compressionLevel);
}