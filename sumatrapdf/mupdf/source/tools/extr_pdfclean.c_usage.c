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
		"usage: mutool clean [options] input.pdf [output.pdf] [pages]\n"
		"\t-p -\tpassword\n"
		"\t-g\tgarbage collect unused objects\n"
		"\t-gg\tin addition to -g compact xref table\n"
		"\t-ggg\tin addition to -gg merge duplicate objects\n"
		"\t-gggg\tin addition to -ggg check streams for duplication\n"
		"\t-l\tlinearize PDF\n"
		"\t-D\tsave file without encryption\n"
		"\t-E -\tsave file with new encryption (rc4-40, rc4-128, aes-128, or aes-256)\n"
		"\t-O -\towner password (only if encrypting)\n"
		"\t-U -\tuser password (only if encrypting)\n"
		"\t-P -\tpermission flags (only if encrypting)\n"
		"\t-a\tascii hex encode binary streams\n"
		"\t-d\tdecompress streams\n"
		"\t-z\tdeflate uncompressed streams\n"
		"\t-f\tcompress font streams\n"
		"\t-i\tcompress image streams\n"
		"\t-c\tclean content streams\n"
		"\t-s\tsanitize content streams\n"
		"\t-A\tcreate appearance streams for annotations\n"
		"\t-AA\trecreate appearance streams for annotations\n"
		"\tpages\tcomma separated list of page numbers and ranges\n"
		);
	exit(1);
}