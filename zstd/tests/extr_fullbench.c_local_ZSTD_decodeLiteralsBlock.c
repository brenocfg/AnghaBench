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

/* Variables and functions */
 size_t ZSTD_decodeLiteralsBlock (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cSize ; 
 int /*<<< orphan*/  g_zdc ; 

__attribute__((used)) static size_t local_ZSTD_decodeLiteralsBlock(const void* src, size_t srcSize, void* dst, size_t dstSize, void* buff2)
{
    (void)src; (void)srcSize; (void)dst; (void)dstSize;
    return ZSTD_decodeLiteralsBlock(g_zdc, buff2, g_cSize);
}