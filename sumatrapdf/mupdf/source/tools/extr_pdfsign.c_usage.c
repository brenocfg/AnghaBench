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
		"usage: mutool sign [options] input.pdf [signature object numbers]\n"
		"\t-p -\tpassword\n"
		"\t-v \tverify signature\n"
		"\t-c \tclear signatures\n"
		"\t-s -\tsign signatures using certificate file\n"
		"\t-P -\tcertificate password\n"
		"\t-o -\toutput file name\n"
		   );
	exit(1);
}