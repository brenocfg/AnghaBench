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
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 char* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 

char *
zfs_strip_partition(char *path)
{
	char *tmp = strdup(path);
	char *part = NULL, *d = NULL;
	if (!tmp)
		return (NULL);

	if ((part = strstr(tmp, "-part")) && part != tmp) {
		d = part + 5;
	} else if ((part = strrchr(tmp, 'p')) &&
	    part > tmp + 1 && isdigit(*(part-1))) {
		d = part + 1;
	} else if ((tmp[0] == 'h' || tmp[0] == 's' || tmp[0] == 'v') &&
	    tmp[1] == 'd') {
		for (d = &tmp[2]; isalpha(*d); part = ++d) { }
	} else if (strncmp("xvd", tmp, 3) == 0) {
		for (d = &tmp[3]; isalpha(*d); part = ++d) { }
	}
	if (part && d && *d != '\0') {
		for (; isdigit(*d); d++) { }
		if (*d == '\0')
			*part = '\0';
	}

	return (tmp);
}