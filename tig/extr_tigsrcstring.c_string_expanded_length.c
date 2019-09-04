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

size_t
string_expanded_length(const char *src, size_t srclen, size_t tabsize, size_t max_size)
{
	size_t size, pos;

	for (size = pos = 0; pos < srclen && size < max_size; pos++) {
		if (src[pos] == '\t') {
			size_t expanded = tabsize - (size % tabsize);

			size += expanded;
		} else {
			size++;
		}
	}

	return pos;
}