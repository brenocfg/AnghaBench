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
struct ext2_inline_data {int /*<<< orphan*/ * ea_data; int /*<<< orphan*/  ea_size; int /*<<< orphan*/  ino; int /*<<< orphan*/  fs; } ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ EXT2_ET_EA_KEY_NOT_FOUND ; 
 scalar_t__ ext2fs_xattr_get (struct ext2_xattr_handle*,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_xattrs_close (struct ext2_xattr_handle**) ; 
 scalar_t__ ext2fs_xattrs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_xattr_handle**) ; 
 scalar_t__ ext2fs_xattrs_read (struct ext2_xattr_handle*) ; 

__attribute__((used)) static errcode_t ext2fs_inline_data_ea_get(struct ext2_inline_data *data)
{
	struct ext2_xattr_handle *handle;
	errcode_t retval;

	data->ea_size = 0;
	data->ea_data = 0;

	retval = ext2fs_xattrs_open(data->fs, data->ino, &handle);
	if (retval)
		return retval;

	retval = ext2fs_xattrs_read(handle);
	if (retval)
		goto err;

	retval = ext2fs_xattr_get(handle, "system.data",
				  (void **)&data->ea_data, &data->ea_size);
	if (retval == EXT2_ET_EA_KEY_NOT_FOUND) {
		data->ea_size = 0;
		data->ea_data = NULL;
		retval = 0;
	} else if (retval)
		goto err;

err:
	(void) ext2fs_xattrs_close(&handle);
	return retval;
}