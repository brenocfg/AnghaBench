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
 int /*<<< orphan*/  B_FALSE ; 
 int MNT_LINE_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
append_options(char *mntopts, char *newopts)
{
	int len = strlen(mntopts);

	/* original length plus new string to append plus 1 for the comma */
	if (len + 1 + strlen(newopts) >= MNT_LINE_MAX) {
		(void) fprintf(stderr, gettext("the opts argument for "
		    "'%s' option is too long (more than %d chars)\n"),
		    "-o", MNT_LINE_MAX);
		usage(B_FALSE);
	}

	if (*mntopts)
		mntopts[len++] = ',';

	(void) strcpy(&mntopts[len], newopts);
}