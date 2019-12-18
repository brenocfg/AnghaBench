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
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_c_nbWorkers ; 
 size_t ZSTD_compress2 (int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  g_cstream ; 

__attribute__((used)) static size_t
local_ZSTD_compress_generic_T2_end(const void* src, size_t srcSize,
                                   void* dst, size_t dstCapacity,
                                   void* payload)
{
    (void)payload;
    ZSTD_CCtx_setParameter(g_cstream, ZSTD_c_nbWorkers, 2);
    return ZSTD_compress2(g_cstream, dst, dstCapacity, src, srcSize);
}