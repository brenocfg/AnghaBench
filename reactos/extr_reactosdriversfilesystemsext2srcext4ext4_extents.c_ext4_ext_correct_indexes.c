#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {void* ee_block; } ;
struct ext4_ext_path {TYPE_1__* p_idx; struct ext4_extent_header* p_hdr; struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  void* __le32 ;
struct TYPE_2__ {void* ei_block; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,struct ext4_extent*,struct ext4_extent_header*) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 TYPE_1__* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int ext4_ext_dirty (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext_depth (struct inode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_ext_correct_indexes(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path)
{
	struct ext4_extent_header *eh;
	int depth = ext_depth(inode);
	struct ext4_extent *ex;
	__le32 border;
	int k, err = 0;

	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;

	if (unlikely(ex == NULL || eh == NULL)) {
		EXT4_ERROR_INODE(inode,
				"ex %p == NULL or eh %p == NULL", ex, eh);
		return -EIO;
	}

	if (depth == 0) {
		/* there is no tree at all */
		return 0;
	}

	if (ex != EXT_FIRST_EXTENT(eh)) {
		/* we correct tree if first leaf got modified only */
		return 0;
	}

	/*
	 * TODO: we need correction if border is smaller than current one
	 */
	k = depth - 1;
	border = path[depth].p_ext->ee_block;
	err = ext4_ext_get_access(icb, handle, inode, path + k);
	if (err)
		return err;
	path[k].p_idx->ei_block = border;
	err = ext4_ext_dirty(icb, handle, inode, path + k);
	if (err)
		return err;

	while (k--) {
		/* change all left-side indexes */
		if (path[k+1].p_idx != EXT_FIRST_INDEX(path[k+1].p_hdr))
			break;
		err = ext4_ext_get_access(icb, handle, inode, path + k);
		if (err)
			break;
		path[k].p_idx->ei_block = border;
		err = ext4_ext_dirty(icb, handle, inode, path + k);
		if (err)
			break;
	}

	return err;
}