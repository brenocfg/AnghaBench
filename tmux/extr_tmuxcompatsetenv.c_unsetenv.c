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
 char** environ ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
unsetenv(const char *name)
{
	char  **envptr;
	int	namelen;

	namelen = strlen(name);
	for (envptr = environ; *envptr != NULL; envptr++) {
		if (strncmp(name, *envptr, namelen) == 0 &&
		    ((*envptr)[namelen] == '=' || (*envptr)[namelen] == '\0'))
			break;
	}
	for (; *envptr != NULL; envptr++)
		*envptr = *(envptr + 1);
	return (0);
}