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
typedef  int mode_t ;

/* Variables and functions */
 int S_ISGID ; 
 int S_ISUID ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_stat_mode (int) ; 

int
main(int argc, char *argv[])
{
	const char *name;
	mode_t extra;

	if (argc < 2) {
		fprintf(stderr, "Invalid argc\n");
		exit(1);
	}

	name = argv[1];
	if (strcmp(name, "SUID") == 0) {
		extra = S_ISUID;
	} else if (strcmp(name, "SGID") == 0) {
		extra = S_ISGID;
	} else if (strcmp(name, "SUID_SGID") == 0) {
		extra = S_ISUID | S_ISGID;
	} else if (strcmp(name, "NONE") == 0) {
		extra = 0;
	} else {
		fprintf(stderr, "Invalid name %s\n", name);
		exit(1);
	}

	test_stat_mode(extra);

	return (0);
}