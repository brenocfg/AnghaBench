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
 char* getprogname () ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* strrchr (char const*,char) ; 

int
areshell(const char *shell)
{
	const char	*progname, *ptr;

	if ((ptr = strrchr(shell, '/')) != NULL)
		ptr++;
	else
		ptr = shell;
	progname = getprogname();
	if (*progname == '-')
		progname++;
	if (strcmp(ptr, progname) == 0)
		return (1);
	return (0);
}