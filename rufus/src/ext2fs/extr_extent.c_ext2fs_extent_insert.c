#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct extent_path {scalar_t__ entries; scalar_t__ max_entries; int left; scalar_t__ buf; struct ext3_extent_idx* curr; } ;
struct ext3_extent_idx {int dummy; } ;
struct ext3_extent_header {int /*<<< orphan*/  eh_entries; } ;
struct ext2fs_extent {int dummy; } ;
typedef  TYPE_2__* ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
struct TYPE_10__ {int ino; int level; struct extent_path* path; TYPE_1__* fs; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_CANT_INSERT_EXTENT ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXTENT_HANDLE ; 
 scalar_t__ EXT2_ET_NO_CURRENT_NODE ; 
 scalar_t__ EXT2_ET_RO_FILSYS ; 
 int EXT2_EXTENT_INSERT_AFTER ; 
 int EXT2_EXTENT_INSERT_NOSPLIT ; 
 int EXT2_FLAG_RW ; 
 struct ext3_extent_idx* EXT_FIRST_INDEX (struct ext3_extent_header*) ; 
 int /*<<< orphan*/  dbg_print_extent (int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 int /*<<< orphan*/  ext2fs_cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_extent_delete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_replace (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 scalar_t__ extent_node_split (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memmove (struct ext3_extent_idx*,struct ext3_extent_idx*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ update_path (TYPE_2__*) ; 

errcode_t ext2fs_extent_insert(ext2_extent_handle_t handle, int flags,
				      struct ext2fs_extent *extent)
{
	struct extent_path		*path;
	struct ext3_extent_idx		*ix;
	struct ext3_extent_header	*eh;
	errcode_t			retval;

	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EXTENT_HANDLE);

	if (!(handle->fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	if (!handle->path)
		return EXT2_ET_NO_CURRENT_NODE;

#ifdef DEBUG
	printf("extent insert: %u ", handle->ino);
	dbg_print_extent(0, extent);
#endif

	path = handle->path + handle->level;

	if (path->entries >= path->max_entries) {
		if (flags & EXT2_EXTENT_INSERT_NOSPLIT) {
			return EXT2_ET_CANT_INSERT_EXTENT;
		} else {
#ifdef DEBUG
			printf("node full (level %d) - splitting\n",
				   handle->level);
#endif
			retval = extent_node_split(handle, 1);
			if (retval)
				return retval;
			path = handle->path + handle->level;
		}
	}

	eh = (struct ext3_extent_header *) path->buf;
	if (path->curr) {
		ix = path->curr;
		if (flags & EXT2_EXTENT_INSERT_AFTER) {
			ix++;
			path->left--;
		}
	} else {
		ix = EXT_FIRST_INDEX(eh);
		path->left = -1;
	}

	path->curr = ix;

	if (path->left >= 0)
		memmove(ix + 1, ix,
			(path->left+1) * sizeof(struct ext3_extent_idx));
	path->left++;
	path->entries++;

	eh = (struct ext3_extent_header *) path->buf;
	eh->eh_entries = ext2fs_cpu_to_le16(path->entries);

	retval = ext2fs_extent_replace(handle, 0, extent);
	if (retval)
		goto errout;

	retval = update_path(handle);
	if (retval)
		goto errout;

	return 0;

errout:
	ext2fs_extent_delete(handle, 0);
	return retval;
}