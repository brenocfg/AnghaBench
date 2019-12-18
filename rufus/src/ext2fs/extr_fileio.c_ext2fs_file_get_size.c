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
typedef  int ext2_off_t ;
typedef  int /*<<< orphan*/  ext2_file_t ;
typedef  int __u64 ;

/* Variables and functions */
 scalar_t__ ext2fs_file_get_lsize (int /*<<< orphan*/ ,int*) ; 

ext2_off_t ext2fs_file_get_size(ext2_file_t file)
{
	__u64	size;

	if (ext2fs_file_get_lsize(file, &size))
		return 0;
	if ((size >> 32) != 0)
		return 0;
	return size;
}