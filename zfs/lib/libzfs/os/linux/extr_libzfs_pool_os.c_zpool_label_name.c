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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rand () ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zpool_label_name(char *label_name, int label_size)
{
	uint64_t id = 0;
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd >= 0) {
		if (read(fd, &id, sizeof (id)) != sizeof (id))
			id = 0;

		close(fd);
	}

	if (id == 0)
		id = (((uint64_t)rand()) << 32) | (uint64_t)rand();

	snprintf(label_name, label_size, "zfs-%016llx", (u_longlong_t)id);
}