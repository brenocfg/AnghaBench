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
 char* getexecname () ; 
 char const* pname ; 
 char* strrchr (char*,char) ; 

const char *
uu_setpname(char *arg0)
{
	/*
	 * Having a NULL argv[0], while uncommon, is possible.  It
	 * makes more sense to handle this event in uu_setpname rather
	 * than in each of its consumers.
	 */
	if (arg0 == NULL) {
		pname = getexecname();
		if (pname == NULL)
			pname = "unknown_command";
		return (pname);
	}

	/*
	 * Guard against '/' at end of command invocation.
	 */
	for (;;) {
		char *p = strrchr(arg0, '/');
		if (p == NULL) {
			pname = arg0;
			break;
		} else {
			if (*(p + 1) == '\0') {
				*p = '\0';
				continue;
			}

			pname = p + 1;
			break;
		}
	}

	return (pname);
}