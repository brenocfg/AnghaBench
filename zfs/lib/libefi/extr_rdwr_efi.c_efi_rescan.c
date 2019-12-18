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
 int /*<<< orphan*/  BLKRRPART ; 
 scalar_t__ EBUSY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usleep (int) ; 

int
efi_rescan(int fd)
{
	int retry = 10;
	int error;

	/* Notify the kernel a devices partition table has been updated */
	while ((error = ioctl(fd, BLKRRPART)) != 0) {
		if ((--retry == 0) || (errno != EBUSY)) {
			(void) fprintf(stderr, "the kernel failed to rescan "
			    "the partition table: %d\n", errno);
			return (-1);
		}
		usleep(50000);
	}

	return (0);
}