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
struct ext2_xattr_handle {unsigned int flags; } ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (struct ext2_xattr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EA_HANDLE ; 

errcode_t ext2fs_xattrs_flags(struct ext2_xattr_handle *handle,
			      unsigned int *new_flags, unsigned int *old_flags)
{
	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EA_HANDLE);
	if (old_flags)
		*old_flags = handle->flags;
	if (new_flags)
		handle->flags = *new_flags;
	return 0;
}