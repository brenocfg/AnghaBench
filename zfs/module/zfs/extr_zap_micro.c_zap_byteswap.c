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
 scalar_t__ ZBT_MICRO ; 
 int /*<<< orphan*/  fzap_byteswap (void*,size_t) ; 
 int /*<<< orphan*/  mzap_byteswap (void*,size_t) ; 

void
zap_byteswap(void *buf, size_t size)
{
	uint64_t block_type = *(uint64_t *)buf;

	if (block_type == ZBT_MICRO || block_type == BSWAP_64(ZBT_MICRO)) {
		/* ASSERT(magic == ZAP_LEAF_MAGIC); */
		mzap_byteswap(buf, size);
	} else {
		fzap_byteswap(buf, size);
	}
}