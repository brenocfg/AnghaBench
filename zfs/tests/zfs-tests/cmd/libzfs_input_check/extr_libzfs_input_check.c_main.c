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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  libzfs_core_fini () ; 
 int /*<<< orphan*/  libzfs_core_init () ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int unexpected_failures ; 
 int /*<<< orphan*/  validate_ioc_values () ; 
 scalar_t__ zfs_fd ; 
 int /*<<< orphan*/  zfs_ioc_input_tests (char const*) ; 

int
main(int argc, const char *argv[])
{
	if (argc != 2) {
		(void) fprintf(stderr, "usage: %s <pool>\n", argv[0]);
		exit(2);
	}

	if (!validate_ioc_values()) {
		(void) fprintf(stderr, "WARNING: zfs_ioc_t has binary "
		    "incompatible command values\n");
		exit(3);
	}

	(void) libzfs_core_init();
	zfs_fd = open(ZFS_DEV, O_RDWR);
	if (zfs_fd < 0) {
		(void) fprintf(stderr, "open: %s\n", strerror(errno));
		libzfs_core_fini();
		exit(2);
	}

	zfs_ioc_input_tests(argv[1]);

	(void) close(zfs_fd);
	libzfs_core_fini();

	return (unexpected_failures);
}