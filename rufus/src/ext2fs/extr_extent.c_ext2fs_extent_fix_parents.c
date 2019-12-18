#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct extent_path {int left; int entries; int /*<<< orphan*/  curr; } ;
struct ext2fs_extent {scalar_t__ e_lblk; int /*<<< orphan*/  e_len; } ;
struct ext2_extent_info {int max_depth; int curr_level; } ;
typedef  TYPE_2__* ext2_extent_handle_t ;
typedef  int errcode_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_11__ {int level; struct extent_path* path; TYPE_1__* fs; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXTENT_HANDLE ; 
 int EXT2_ET_NO_CURRENT_NODE ; 
 int EXT2_ET_RO_FILSYS ; 
 int /*<<< orphan*/  EXT2_EXTENT_CURRENT ; 
 int /*<<< orphan*/  EXT2_EXTENT_UP ; 
 int EXT2_FLAG_RW ; 
 int ext2fs_extent_get (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 int ext2fs_extent_get_info (TYPE_2__*,struct ext2_extent_info*) ; 
 int ext2fs_extent_goto2 (TYPE_2__*,int,scalar_t__) ; 
 int ext2fs_extent_replace (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 int /*<<< orphan*/  update_path (TYPE_2__*) ; 

errcode_t ext2fs_extent_fix_parents(ext2_extent_handle_t handle)
{
	int				retval = 0;
	int				orig_height;
	blk64_t				start;
	struct extent_path		*path;
	struct ext2fs_extent		extent;
	struct ext2_extent_info		info;

	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EXTENT_HANDLE);

	if (!(handle->fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	if (!handle->path)
		return EXT2_ET_NO_CURRENT_NODE;

	path = handle->path + handle->level;
	if (!path->curr)
		return EXT2_ET_NO_CURRENT_NODE;

	retval = ext2fs_extent_get(handle, EXT2_EXTENT_CURRENT, &extent);
	if (retval)
		goto done;

	/* modified node's start block */
	start = extent.e_lblk;

	if ((retval = ext2fs_extent_get_info(handle, &info)))
		return retval;
	orig_height = info.max_depth - info.curr_level;

	/* traverse up until index not first, or startblk matches, or top */
	while (handle->level > 0 &&
	       (path->left == path->entries - 1)) {
		retval = ext2fs_extent_get(handle, EXT2_EXTENT_UP, &extent);
		if (retval)
			goto done;
		if (extent.e_lblk == start)
			break;
		path = handle->path + handle->level;
		extent.e_len += (extent.e_lblk - start);
		extent.e_lblk = start;
		retval = ext2fs_extent_replace(handle, 0, &extent);
		if (retval)
			goto done;
		update_path(handle);
	}

	/* put handle back to where we started */
	retval = ext2fs_extent_goto2(handle, orig_height, start);
done:
	return retval;
}