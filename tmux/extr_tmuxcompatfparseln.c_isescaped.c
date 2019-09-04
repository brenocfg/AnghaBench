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

__attribute__((used)) static int
isescaped(const char *sp, const char *p, int esc)
{
	const char     *cp;
	size_t		ne;

	/* No escape character */
	if (esc == '\0')
		return 1;

	/* Count the number of escape characters that precede ours */
	for (ne = 0, cp = p; --cp >= sp && *cp == esc; ne++)
		continue;

	/* Return true if odd number of escape characters */
	return (ne & 1) != 0;
}