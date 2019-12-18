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
typedef  scalar_t__ uint_t ;
typedef  scalar_t__ diskaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKGETSIZE64 ; 
 int /*<<< orphan*/  BLKSSZGET ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
read_disk_info(int fd, diskaddr_t *capacity, uint_t *lbsize)
{
	int sector_size;
	unsigned long long capacity_size;

	if (ioctl(fd, BLKSSZGET, &sector_size) < 0)
		return (-1);

	if (ioctl(fd, BLKGETSIZE64, &capacity_size) < 0)
		return (-1);

	*lbsize = (uint_t)sector_size;
	*capacity = (diskaddr_t)(capacity_size / sector_size);

	return (0);
}