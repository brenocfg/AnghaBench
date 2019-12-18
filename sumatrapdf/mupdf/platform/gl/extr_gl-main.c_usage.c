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
 char* FZ_VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *argv0)
{
	fprintf(stderr, "mupdf-gl version %s\n", FZ_VERSION);
	fprintf(stderr, "usage: %s [options] document [page]\n", argv0);
	fprintf(stderr, "\t-p -\tpassword\n");
	fprintf(stderr, "\t-r -\tresolution\n");
	fprintf(stderr, "\t-I\tinvert colors\n");
	fprintf(stderr, "\t-W -\tpage width for EPUB layout\n");
	fprintf(stderr, "\t-H -\tpage height for EPUB layout\n");
	fprintf(stderr, "\t-S -\tfont size for EPUB layout\n");
	fprintf(stderr, "\t-U -\tuser style sheet for EPUB layout\n");
	fprintf(stderr, "\t-X\tdisable document styles for EPUB layout\n");
	fprintf(stderr, "\t-J\tdisable javascript in PDF forms\n");
	fprintf(stderr, "\t-A -\tset anti-aliasing level (0-8,9,10)\n");
	fprintf(stderr, "\t-B -\tset black tint color (default: 303030)\n");
	fprintf(stderr, "\t-C -\tset white tint color (default: FFFFF0)\n");
	exit(1);
}