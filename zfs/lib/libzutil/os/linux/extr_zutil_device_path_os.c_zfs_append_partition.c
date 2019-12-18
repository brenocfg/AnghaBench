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
 char* UDISK_ROOT ; 
 char* ZVOL_ROOT ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
zfs_append_partition(char *path, size_t max_len)
{
	int len = strlen(path);

	if ((strncmp(path, UDISK_ROOT, strlen(UDISK_ROOT)) == 0) ||
	    (strncmp(path, ZVOL_ROOT, strlen(ZVOL_ROOT)) == 0)) {
		if (len + 6 >= max_len)
			return (-1);

		(void) strcat(path, "-part1");
		len += 6;
	} else {
		if (len + 2 >= max_len)
			return (-1);

		if (isdigit(path[len-1])) {
			(void) strcat(path, "p1");
			len += 2;
		} else {
			(void) strcat(path, "1");
			len += 1;
		}
	}

	return (len);
}