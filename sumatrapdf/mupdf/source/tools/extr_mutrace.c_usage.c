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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr,
		"Usage: mutool trace [options] file [pages]\n"
		"\t-p -\tpassword\n"
		"\n"
		"\t-W -\tpage width for EPUB layout\n"
		"\t-H -\tpage height for EPUB layout\n"
		"\t-S -\tfont size for EPUB layout\n"
		"\t-U -\tfile name of user stylesheet for EPUB layout\n"
		"\t-X\tdisable document styles for EPUB layout\n"
		"\n"
		"\t-d\tuse display list\n"
		"\n"
		"\tpages\tcomma separated list of page numbers and ranges\n"
		);
	exit(1);
}