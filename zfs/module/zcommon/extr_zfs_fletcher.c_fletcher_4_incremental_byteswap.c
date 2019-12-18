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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  fletcher_4_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 size_t SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  fletcher_4_incremental_impl (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_scalar_byteswap (int /*<<< orphan*/ *,void*,size_t) ; 

int
fletcher_4_incremental_byteswap(void *buf, size_t size, void *data)
{
	zio_cksum_t *zcp = data;
	/* Use scalar impl to directly update cksum of small blocks */
	if (size < SPA_MINBLOCKSIZE)
		fletcher_4_scalar_byteswap((fletcher_4_ctx_t *)zcp, buf, size);
	else
		fletcher_4_incremental_impl(B_FALSE, buf, size, zcp);
	return (0);
}