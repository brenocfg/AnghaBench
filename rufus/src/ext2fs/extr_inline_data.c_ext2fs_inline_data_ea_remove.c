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
struct ext2_xattr_handle {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ ext2fs_xattr_remove (struct ext2_xattr_handle*,char*) ; 
 int /*<<< orphan*/  ext2fs_xattrs_close (struct ext2_xattr_handle**) ; 
 scalar_t__ ext2fs_xattrs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_xattr_handle**) ; 
 scalar_t__ ext2fs_xattrs_read (struct ext2_xattr_handle*) ; 

errcode_t ext2fs_inline_data_ea_remove(ext2_filsys fs, ext2_ino_t ino)
{
	struct ext2_xattr_handle *handle;
	errcode_t retval;

	retval = ext2fs_xattrs_open(fs, ino, &handle);
	if (retval)
		return retval;

	retval = ext2fs_xattrs_read(handle);
	if (retval)
		goto err;

	retval = ext2fs_xattr_remove(handle, "system.data");
err:
	(void) ext2fs_xattrs_close(&handle);
	return retval;
}