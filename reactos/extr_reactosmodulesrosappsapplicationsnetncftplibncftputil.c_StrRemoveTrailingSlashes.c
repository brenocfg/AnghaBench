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
 char* strrchr (char*,char) ; 

void
StrRemoveTrailingSlashes(char *dst)
{
	char *cp;

	cp = strrchr(dst, '/');
	if ((cp == NULL) || (cp[1] != '\0'))
		return;

	/* Note: Do not destroy a path of "/" */
	while ((cp > dst) && (*cp == '/'))
		*cp-- = '\0';
}