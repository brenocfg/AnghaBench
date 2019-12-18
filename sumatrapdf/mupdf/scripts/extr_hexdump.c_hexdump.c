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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fgetc (int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ string ; 

__attribute__((used)) static int
hexdump(FILE *fo, FILE *fi)
{
	int c, n;

	if (string)
		fprintf(fo, "\"");

	n = 0;
	c = fgetc(fi);
	while (c != -1)
	{
		n += fprintf(fo, string ? "\\x%02x" : "%d,", c);
		if (n > 72) {
			fprintf(fo, string ? "\"\n\"" : "\n");
			n = 0;
		}
		c = fgetc(fi);
	}

	if (string)
		fprintf(fo, "\"\n");

	return n;
}