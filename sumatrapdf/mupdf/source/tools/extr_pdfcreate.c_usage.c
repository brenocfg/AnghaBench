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
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pdf_write_options_usage ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr,
		"usage: mutool create [-o output.pdf] [-O options] page.txt [page2.txt ...]\n"
		"\t-o -\tname of PDF file to create\n"
		"\t-O -\tcomma separated list of output options\n"
		"\tpage.txt\tcontent stream with annotations for creating resources\n\n"
		"Content stream special commands:\n"
		"\t%%%%MediaBox LLX LLY URX URY\n"
		"\t%%%%Rotate Angle\n"
		"\t%%%%Font Name Filename (or base 14 font name)\n"
		"\t%%%%CJKFont Name Language WMode Style (Language=zh-Hant|zh-Hans|ja|ko, WMode=H|V, Style=serif|sans)\n"
		"\t%%%%Image Name Filename\n\n"
		);
	fputs(fz_pdf_write_options_usage, stderr);
	exit(1);
}