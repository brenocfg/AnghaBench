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

__attribute__((used)) static size_t
Vt100VisibleStrlen(const char *src)
{
	const char *cp;
	size_t esc;

	for (esc = 0, cp = src; *cp != '\0'; cp++) {
		if (*cp == '\033')
			esc++;
	}

	/* The VT100 escape codes we use are all in the form "\033[7m"
	 * These aren't visible, so subtract them from the count.
	 */
	return ((size_t) (cp - src) - (esc * 4));
}