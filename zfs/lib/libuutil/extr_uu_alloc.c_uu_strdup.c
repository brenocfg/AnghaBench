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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* uu_zalloc (size_t) ; 

char *
uu_strdup(const char *str)
{
	char *buf = NULL;

	if (str != NULL) {
		size_t sz;

		sz = strlen(str) + 1;
		buf = uu_zalloc(sz);
		if (buf != NULL)
			(void) memcpy(buf, str, sz);
	}
	return (buf);
}