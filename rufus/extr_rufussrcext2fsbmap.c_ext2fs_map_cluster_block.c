#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int i_flags; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_5__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int EXT4_EXTENTS_FL ; 
 int /*<<< orphan*/  ext2fs_extent_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_open2 (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_has_feature_bigalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ implied_cluster_alloc (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

errcode_t ext2fs_map_cluster_block(ext2_filsys fs, ext2_ino_t ino,
				   struct ext2_inode *inode, blk64_t lblk,
				   blk64_t *pblk)
{
	ext2_extent_handle_t handle;
	errcode_t retval;

	/* Need bigalloc and extents to be enabled */
	*pblk = 0;
	if (!ext2fs_has_feature_bigalloc(fs->super) ||
	    !(inode->i_flags & EXT4_EXTENTS_FL))
		return 0;

	retval = ext2fs_extent_open2(fs, ino, inode, &handle);
	if (retval)
		goto out;

	retval = implied_cluster_alloc(fs, ino, inode, handle, lblk, pblk);
	if (retval)
		goto out2;

out2:
	ext2fs_extent_free(handle);
out:
	return retval;
}