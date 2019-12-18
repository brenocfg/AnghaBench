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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatalx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strndup (char const*,size_t) ; 

char *
xstrndup(const char *str, size_t maxlen)
{
	char *cp;

	if ((cp = strndup(str, maxlen)) == NULL)
		fatalx("xstrndup: %s", strerror(errno));
	return cp;
}