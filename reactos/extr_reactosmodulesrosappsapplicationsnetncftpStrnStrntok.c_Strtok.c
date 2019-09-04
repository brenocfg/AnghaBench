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
 int /*<<< orphan*/ * strchr (char const*,int) ; 

char *
Strtok(char *buf, const char *delims)
{
	static char *p = NULL;
	char *start, *end;

	if (buf != NULL) {
		p = buf;
	} else {
		if (p == NULL)
			return (NULL);		/* No more tokens. */
	}
	for (start = p, end = p; ; end++) {
		if (*end == '\0') {
			p = NULL;		/* This is the last token. */
			break;
		}
		if (strchr(delims, (int) *end) != NULL) {
			*end++ = '\0';
			p = end;
			break;
		}
	}
	return (start);
}