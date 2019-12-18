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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *argv0)
{
	fprintf(stderr, "usage: %s [options] file.pdf [page]\n", argv0);
	fprintf(stderr, "\t-p -\tpassword\n");
	fprintf(stderr, "\t-r -\tresolution\n");
	fprintf(stderr, "\t-A -\tset anti-aliasing quality in bits (0=off, 8=best)\n");
	fprintf(stderr, "\t-C -\tRRGGBB (tint color in hexadecimal syntax)\n");
	fprintf(stderr, "\t-W -\tpage width for EPUB layout\n");
	fprintf(stderr, "\t-H -\tpage height for EPUB layout\n");
	fprintf(stderr, "\t-I -\tinvert colors\n");
	fprintf(stderr, "\t-S -\tfont size for EPUB layout\n");
	fprintf(stderr, "\t-U -\tuser style sheet for EPUB layout\n");
	fprintf(stderr, "\t-X\tdisable document styles for EPUB layout\n");
	exit(1);
}