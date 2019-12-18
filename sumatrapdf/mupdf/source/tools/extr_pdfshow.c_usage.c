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
		"usage: mutool show [options] file.pdf ( xref | outline | grep | js | <path> ) *\n"
		"\t-p -\tpassword\n"
		"\t-o -\toutput file\n"
		"\t-e\tleave stream contents in their original form\n"
		"\t-b\tprint only stream contents, as raw binary data\n"
		"\t-g\tprint only object, one line per object, suitable for grep\n"
		"\tpath: path to an object, starting with either an object number,\n"
		"\t\t'pages', 'trailer', or a property in the trailer;\n"
		"\t\tpath elements separated by '.' or '/'. Path elements must be\n"
		"\t\tarray index numbers, dictionary property names, or '*'.\n"
	);
	exit(1);
}