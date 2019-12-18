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
 int /*<<< orphan*/  libzfs_core_fini () ; 
 int /*<<< orphan*/  libzfs_core_init () ; 
 char const* pool ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  run_tests () ; 
 int unexpected_failures ; 

int
main(int argc, const char *argv[])
{
	(void) libzfs_core_init();

	if (argc != 2) {
		(void) printf("usage: %s <pool>\n",
		    argv[0]);
		exit(2);
	}
	pool = argv[1];

	run_tests();

	libzfs_core_fini();
	return (unexpected_failures);
}