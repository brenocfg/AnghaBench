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
struct ext2_xattr_handle {int count; int ibody_count; struct ext2_xattr* attrs; int /*<<< orphan*/  fs; } ;
struct ext2_xattr {scalar_t__ ea_ino; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (struct ext2_xattr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EA_HANDLE ; 
 int /*<<< orphan*/  ext2fs_free_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_xattrs_write (struct ext2_xattr_handle*) ; 
 int /*<<< orphan*/  memmove (struct ext2_xattr*,struct ext2_xattr*,int) ; 
 int /*<<< orphan*/  memset (struct ext2_xattr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xattr_inode_dec_ref (int /*<<< orphan*/ ,scalar_t__) ; 

errcode_t ext2fs_xattr_remove(struct ext2_xattr_handle *handle,
			      const char *key)
{
	struct ext2_xattr *x;
	struct ext2_xattr *end = handle->attrs + handle->count;

	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EA_HANDLE);
	for (x = handle->attrs; x < end; x++) {
		if (strcmp(x->name, key) == 0) {
			ext2fs_free_mem(&x->name);
			ext2fs_free_mem(&x->value);
			if (x->ea_ino)
				xattr_inode_dec_ref(handle->fs, x->ea_ino);
			memmove(x, x + 1, (end - x - 1)*sizeof(*x));
			memset(end - 1, 0, sizeof(*end));
			if (x < handle->attrs + handle->ibody_count)
				handle->ibody_count--;
			handle->count--;
			return ext2fs_xattrs_write(handle);
		}
	}

	/* no key found, success! */
	return 0;
}