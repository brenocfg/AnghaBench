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
typedef  scalar_t__ ext2_off_t ;
typedef  int /*<<< orphan*/  ext2_file_t ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_file_llseek (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 

errcode_t ext2fs_file_lseek(ext2_file_t file, ext2_off_t offset,
			    int whence, ext2_off_t *ret_pos)
{
	__u64		loffset, ret_loffset = 0;
	errcode_t	retval;

	loffset = offset;
	retval = ext2fs_file_llseek(file, loffset, whence, &ret_loffset);
	if (ret_pos)
		*ret_pos = (ext2_off_t) ret_loffset;
	return retval;
}