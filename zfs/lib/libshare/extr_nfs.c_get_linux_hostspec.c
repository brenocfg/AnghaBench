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
 int SA_NO_MEMORY ; 
 int SA_OK ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
get_linux_hostspec(const char *solaris_hostspec, char **plinux_hostspec)
{
	/*
	 * For now we just support CIDR masks (e.g. @192.168.0.0/16) and host
	 * wildcards (e.g. *.example.org).
	 */
	if (solaris_hostspec[0] == '@') {
		/*
		 * Solaris host specifier, e.g. @192.168.0.0/16; we just need
		 * to skip the @ in this case
		 */
		*plinux_hostspec = strdup(solaris_hostspec + 1);
	} else {
		*plinux_hostspec = strdup(solaris_hostspec);
	}

	if (*plinux_hostspec == NULL) {
		return (SA_NO_MEMORY);
	}

	return (SA_OK);
}