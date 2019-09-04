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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t ext2fs_djb2_hash(const void *str, size_t size)
{
	int c;
	const char *s = str;
	uint32_t hash = 5381;

	while (size-- > 0) {
		c = *s++;
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}