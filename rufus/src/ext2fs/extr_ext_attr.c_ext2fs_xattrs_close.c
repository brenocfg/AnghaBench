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
struct ext2_xattr_handle {struct ext2_xattr_handle* attrs; } ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (struct ext2_xattr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EA_HANDLE ; 
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2_xattr_handle**) ; 
 int /*<<< orphan*/  xattrs_free_keys (struct ext2_xattr_handle*) ; 

errcode_t ext2fs_xattrs_close(struct ext2_xattr_handle **handle)
{
	struct ext2_xattr_handle *h = *handle;

	EXT2_CHECK_MAGIC(h, EXT2_ET_MAGIC_EA_HANDLE);
	xattrs_free_keys(h);
	ext2fs_free_mem(&h->attrs);
	ext2fs_free_mem(handle);
	return 0;
}