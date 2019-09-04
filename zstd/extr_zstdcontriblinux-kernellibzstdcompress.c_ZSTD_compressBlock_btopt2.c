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

__attribute__((used)) static void ZSTD_compressBlock_btopt2(ZSTD_CCtx *ctx, const void *src, size_t srcSize)
{
#ifdef ZSTD_OPT_H_91842398743
	ZSTD_compressBlock_opt_generic(ctx, src, srcSize, 1);
#else
	(void)ctx;
	(void)src;
	(void)srcSize;
	return;
#endif
}