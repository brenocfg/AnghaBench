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
typedef  scalar_t__ uint64_t ;
struct block_device {int /*<<< orphan*/  bd_inode; struct block_device* bd_contains; int /*<<< orphan*/ * bd_part; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EFI_MIN_RESV_SIZE ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int NEW_START_BLOCK ; 
 int PARTITION_END_ALIGNMENT ; 
 int SECTOR_BITS ; 
 scalar_t__ bdev_capacity (struct block_device*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
bdev_max_capacity(struct block_device *bdev, uint64_t wholedisk)
{
	uint64_t psize;
	int64_t available;

	if (wholedisk && bdev->bd_part != NULL && bdev != bdev->bd_contains) {
		/*
		 * When reporting maximum expansion capacity for a wholedisk
		 * deduct any capacity which is expected to be lost due to
		 * alignment restrictions.  Over reporting this value isn't
		 * harmful and would only result in slightly less capacity
		 * than expected post expansion.
		 * The estimated available space may be slightly smaller than
		 * bdev_capacity() for devices where the number of sectors is
		 * not a multiple of the alignment size and the partition layout
		 * is keeping less than PARTITION_END_ALIGNMENT bytes after the
		 * "reserved" EFI partition: in such cases return the device
		 * usable capacity.
		 */
		available = i_size_read(bdev->bd_contains->bd_inode) -
		    ((EFI_MIN_RESV_SIZE + NEW_START_BLOCK +
		    PARTITION_END_ALIGNMENT) << SECTOR_BITS);
		psize = MAX(available, bdev_capacity(bdev));
	} else {
		psize = bdev_capacity(bdev);
	}

	return (psize);
}