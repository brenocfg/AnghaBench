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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ BSWAP_64 (scalar_t__) ; 
 scalar_t__ ZBT_LEAF ; 
 int /*<<< orphan*/  byteswap_uint64_array (void*,size_t) ; 
 int /*<<< orphan*/  zap_leaf_byteswap (void*,size_t) ; 

void
fzap_byteswap(void *vbuf, size_t size)
{
	uint64_t block_type = *(uint64_t *)vbuf;

	if (block_type == ZBT_LEAF || block_type == BSWAP_64(ZBT_LEAF))
		zap_leaf_byteswap(vbuf, size);
	else {
		/* it's a ptrtbl block */
		byteswap_uint64_array(vbuf, size);
	}
}