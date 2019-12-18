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
 scalar_t__ IsLocalPathDelim (int) ; 

__attribute__((used)) static char *
_StrRFindLocalPathDelim(const char *src)	/* TODO: optimize */
{
	const char *last;
	int c;

	last = NULL;
	for (;;) {
		c = *src++;
		if (c == '\0')
			break;
		if (IsLocalPathDelim(c))
			last = src - 1;
	}

	return ((char *) last);
}