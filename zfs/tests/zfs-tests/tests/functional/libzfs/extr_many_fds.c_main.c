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
struct rlimit {int rlim_cur; int rlim_max; } ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

int
main(int argc, char **argv)
{
	int i;
	struct rlimit limit;
	libzfs_handle_t *h;

	limit.rlim_cur = 65535;
	limit.rlim_max = 65535;

	if (setrlimit(RLIMIT_NOFILE, &limit) != 0) {
		(void) printf("many_fds: setrlimit() failed with errno=%d\n",
		    errno);
		exit(1);
	}

	for (i = 0; i < 255; ++i) {
		int fd = open("/dev/null", O_RDONLY);
		if (fd == -1) {
			(void) printf("open failed with errno=%d\n", errno);
			return (1);
		}
	}

	h = libzfs_init();

	if (h != NULL) {
		libzfs_fini(h);
		return (0);
	} else {
		(void) printf("many_fds: libzfs_init() failed with errno=%d\n",
		    errno);
		return (1);
	}
}