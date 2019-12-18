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

__attribute__((used)) static void
compress_slashes(const char *src, char *dest)
{
	while (*src != '\0') {
		*dest = *src++;
		while (*dest == '/' && *src == '/')
			++src;
		++dest;
	}
	*dest = '\0';
}