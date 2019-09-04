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
typedef  int /*<<< orphan*/  zero_buf ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,char const*,size_t) ; 

int ext2fs_mem_is_zero(const char *mem, size_t len)
{
	static const char zero_buf[256];

	while (len >= sizeof(zero_buf)) {
		if (memcmp(mem, zero_buf, sizeof(zero_buf)))
			return 0;
		len -= sizeof(zero_buf);
		mem += sizeof(zero_buf);
	}
	/* Deal with leftover bytes. */
	if (len)
		return !memcmp(mem, zero_buf, len);
	return 1;
}