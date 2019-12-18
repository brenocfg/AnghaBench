#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct extent_path {scalar_t__ entries; } ;
struct ext2fs_extent {int e_len; scalar_t__ e_pblk; scalar_t__ e_lblk; int e_flags; } ;
struct ext2_extent_info {int max_depth; int curr_level; } ;
typedef  int /*<<< orphan*/  extent ;
typedef  TYPE_2__* ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;
typedef  int __u32 ;
struct TYPE_14__ {int ino; int level; int max_depth; struct extent_path* path; TYPE_1__* fs; } ;
struct TYPE_13__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_EXTENT_NOT_FOUND ; 
 scalar_t__ EXT2_ET_EXTENT_NO_NEXT ; 
 scalar_t__ EXT2_ET_EXTENT_NO_PREV ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXTENT_HANDLE ; 
 scalar_t__ EXT2_ET_NO_CURRENT_NODE ; 
 scalar_t__ EXT2_ET_RO_FILSYS ; 
 int /*<<< orphan*/  EXT2_EXTENT_CURRENT ; 
 int EXT2_EXTENT_FLAGS_LEAF ; 
 int EXT2_EXTENT_FLAGS_UNINIT ; 
 int /*<<< orphan*/  EXT2_EXTENT_INSERT_AFTER ; 
 int /*<<< orphan*/  EXT2_EXTENT_NEXT_LEAF ; 
 int /*<<< orphan*/  EXT2_EXTENT_PREV_LEAF ; 
 int EXT2_EXTENT_SET_BMAP_UNINIT ; 
 int EXT2_FLAG_RW ; 
 int EXT_INIT_MAX_LEN ; 
 int EXT_UNINIT_MAX_LEN ; 
 int /*<<< orphan*/  dbg_print_extent (char*,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_delete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_fix_parents (TYPE_2__*) ; 
 scalar_t__ ext2fs_extent_get (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_get_info (TYPE_2__*,struct ext2_extent_info*) ; 
 scalar_t__ ext2fs_extent_goto (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_extent_goto2 (TYPE_2__*,int,scalar_t__) ; 
 scalar_t__ ext2fs_extent_insert (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_replace (TYPE_2__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 int /*<<< orphan*/  memset (struct ext2fs_extent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

errcode_t ext2fs_extent_set_bmap(ext2_extent_handle_t handle,
				 blk64_t logical, blk64_t physical, int flags)
{
	errcode_t		ec, retval = 0;
	int			mapped = 1; /* logical is mapped? */
	int			orig_height;
	int			extent_uninit = 0;
	int			prev_uninit = 0;
	int			next_uninit = 0;
	int			new_uninit = 0;
	int			max_len = EXT_INIT_MAX_LEN;
	int			has_prev, has_next;
	blk64_t			orig_lblk;
	struct extent_path	*path;
	struct ext2fs_extent	extent, next_extent, prev_extent;
	struct ext2fs_extent	newextent;
	struct ext2_extent_info	info;

	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EXTENT_HANDLE);

#ifdef DEBUG
	printf("set_bmap ino %u log %lld phys %lld flags %d\n",
	       handle->ino, logical, physical, flags);
#endif

	if (!(handle->fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	if (!handle->path)
		return EXT2_ET_NO_CURRENT_NODE;

	path = handle->path + handle->level;

	if (flags & EXT2_EXTENT_SET_BMAP_UNINIT) {
		new_uninit = 1;
		max_len = EXT_UNINIT_MAX_LEN;
	}

	/* if (re)mapping, set up new extent to insert */
	if (physical) {
		newextent.e_len = 1;
		newextent.e_pblk = physical;
		newextent.e_lblk = logical;
		newextent.e_flags = EXT2_EXTENT_FLAGS_LEAF;
		if (new_uninit)
			newextent.e_flags |= EXT2_EXTENT_FLAGS_UNINIT;
	}

	/* special case if the extent tree is completely empty */
	if ((handle->max_depth == 0) && (path->entries == 0)) {
		retval = ext2fs_extent_insert(handle, 0, &newextent);
		return retval;
	}

	/* save our original location in the extent tree */
	if ((retval = ext2fs_extent_get(handle, EXT2_EXTENT_CURRENT,
					&extent))) {
		if (retval != EXT2_ET_NO_CURRENT_NODE)
			return retval;
		memset(&extent, 0, sizeof(extent));
	}
	if ((retval = ext2fs_extent_get_info(handle, &info)))
		return retval;
	orig_height = info.max_depth - info.curr_level;
	orig_lblk = extent.e_lblk;

	/* go to the logical spot we want to (re/un)map */
	retval = ext2fs_extent_goto(handle, logical);
	if (retval) {
		if (retval == EXT2_ET_EXTENT_NOT_FOUND) {
			retval = 0;
			mapped = 0;
			if (!physical) {
#ifdef DEBUG
				printf("block %llu already unmapped\n",
					logical);
#endif
				goto done;
			}
		} else
			goto done;
	}

	/*
	 * This may be the extent *before* the requested logical,
	 * if it's currently unmapped.
	 *
	 * Get the previous and next leaf extents, if they are present.
	 */
	retval = ext2fs_extent_get(handle, EXT2_EXTENT_CURRENT, &extent);
	if (retval)
		goto done;
	if (extent.e_flags & EXT2_EXTENT_FLAGS_UNINIT)
		extent_uninit = 1;
	retval = ext2fs_extent_get(handle, EXT2_EXTENT_NEXT_LEAF, &next_extent);
	if (retval) {
		has_next = 0;
		if (retval != EXT2_ET_EXTENT_NO_NEXT)
			goto done;
	} else {
		dbg_print_extent("set_bmap: next_extent",
				 &next_extent);
		has_next = 1;
		if (next_extent.e_flags & EXT2_EXTENT_FLAGS_UNINIT)
			next_uninit = 1;
	}
	retval = ext2fs_extent_goto(handle, logical);
	if (retval && retval != EXT2_ET_EXTENT_NOT_FOUND)
		goto done;
	retval = ext2fs_extent_get(handle, EXT2_EXTENT_PREV_LEAF, &prev_extent);
	if (retval) {
		has_prev = 0;
		if (retval != EXT2_ET_EXTENT_NO_PREV)
			goto done;
	} else {
		has_prev = 1;
		dbg_print_extent("set_bmap: prev_extent",
				 &prev_extent);
		if (prev_extent.e_flags & EXT2_EXTENT_FLAGS_UNINIT)
			prev_uninit = 1;
	}
	retval = ext2fs_extent_goto(handle, logical);
	if (retval && retval != EXT2_ET_EXTENT_NOT_FOUND)
		goto done;

	/* check if already pointing to the requested physical */
	if (mapped && (new_uninit == extent_uninit) &&
	    (extent.e_pblk + (logical - extent.e_lblk) == physical)) {
#ifdef DEBUG
		printf("physical block (at %llu) unchanged\n", logical);
#endif
		goto done;
	}

	if (!mapped) {
#ifdef DEBUG
		printf("mapping unmapped logical block %llu\n", logical);
#endif
		if ((logical == extent.e_lblk + extent.e_len) &&
		    (physical == extent.e_pblk + extent.e_len) &&
		    (new_uninit == extent_uninit) &&
		    ((int) extent.e_len < max_len-1)) {
			extent.e_len++;
			retval = ext2fs_extent_replace(handle, 0, &extent);
		} else if ((logical == extent.e_lblk - 1) &&
			   (physical == extent.e_pblk - 1) &&
			   (new_uninit == extent_uninit) &&
			   ((int) extent.e_len < max_len - 1)) {
			extent.e_len++;
			extent.e_lblk--;
			extent.e_pblk--;
			retval = ext2fs_extent_replace(handle, 0, &extent);
		} else if (has_next &&
			   (logical == next_extent.e_lblk - 1) &&
			   (physical == next_extent.e_pblk - 1) &&
			   (new_uninit == next_uninit) &&
			   ((int) next_extent.e_len < max_len - 1)) {
			retval = ext2fs_extent_get(handle,
						   EXT2_EXTENT_NEXT_LEAF,
						   &next_extent);
			if (retval)
				goto done;
			next_extent.e_len++;
			next_extent.e_lblk--;
			next_extent.e_pblk--;
			retval = ext2fs_extent_replace(handle, 0, &next_extent);
		} else if (logical < extent.e_lblk)
			retval = ext2fs_extent_insert(handle, 0, &newextent);
		else
			retval = ext2fs_extent_insert(handle,
				      EXT2_EXTENT_INSERT_AFTER, &newextent);
		if (retval)
			goto done;
		retval = ext2fs_extent_fix_parents(handle);
		if (retval)
			goto done;
	} else if ((logical == extent.e_lblk) && (extent.e_len == 1))  {
#ifdef DEBUG
		printf("(re/un)mapping only block in extent\n");
#endif
		if (physical) {
			retval = ext2fs_extent_replace(handle, 0, &newextent);
		} else {
			retval = ext2fs_extent_delete(handle, 0);
			if (retval)
				goto done;
			ec = ext2fs_extent_fix_parents(handle);
			if (ec != EXT2_ET_NO_CURRENT_NODE)
				retval = ec;
		}

		if (retval)
			goto done;
	} else if (logical == extent.e_lblk + extent.e_len - 1)  {
#ifdef DEBUG
		printf("(re/un)mapping last block in extent\n");
#endif
		if (physical) {
			if (has_next &&
			    (logical == (next_extent.e_lblk - 1)) &&
			    (physical == (next_extent.e_pblk - 1)) &&
			    (new_uninit == next_uninit) &&
			    ((int) next_extent.e_len < max_len - 1)) {
				retval = ext2fs_extent_get(handle,
					EXT2_EXTENT_NEXT_LEAF, &next_extent);
				if (retval)
					goto done;
				next_extent.e_len++;
				next_extent.e_lblk--;
				next_extent.e_pblk--;
				retval = ext2fs_extent_replace(handle, 0,
							       &next_extent);
				if (retval)
					goto done;
			} else
				retval = ext2fs_extent_insert(handle,
				      EXT2_EXTENT_INSERT_AFTER, &newextent);
			if (retval)
				goto done;
			retval = ext2fs_extent_fix_parents(handle);
			if (retval)
				goto done;
			/*
			 * Now pointing at inserted extent; move back to prev.
			 *
			 * We cannot use EXT2_EXTENT_PREV to go back; note the
			 * subtlety in the comment for fix_parents().
			 */
			retval = ext2fs_extent_goto(handle, logical);
			if (retval)
				goto done;
			retval = ext2fs_extent_get(handle,
						   EXT2_EXTENT_CURRENT,
						   &extent);
			if (retval)
				goto done;
		}
		extent.e_len--;
		retval = ext2fs_extent_replace(handle, 0, &extent);
		if (retval)
			goto done;
	} else if (logical == extent.e_lblk) {
#ifdef DEBUG
		printf("(re/un)mapping first block in extent\n");
#endif
		if (physical) {
			if (has_prev &&
			    (logical == (prev_extent.e_lblk +
					 prev_extent.e_len)) &&
			    (physical == (prev_extent.e_pblk +
					  prev_extent.e_len)) &&
			    (new_uninit == prev_uninit) &&
			    ((int) prev_extent.e_len < max_len-1)) {
				retval = ext2fs_extent_get(handle, 
					EXT2_EXTENT_PREV_LEAF, &prev_extent);
				if (retval)
					goto done;
				prev_extent.e_len++;
				retval = ext2fs_extent_replace(handle, 0,
							       &prev_extent);
			} else
				retval = ext2fs_extent_insert(handle,
							      0, &newextent);
			if (retval)
				goto done;
			retval = ext2fs_extent_fix_parents(handle);
			if (retval)
				goto done;
			retval = ext2fs_extent_get(handle,
						   EXT2_EXTENT_NEXT_LEAF,
						   &extent);
			if (retval)
				goto done;
		}
		extent.e_pblk++;
		extent.e_lblk++;
		extent.e_len--;
		retval = ext2fs_extent_replace(handle, 0, &extent);
		if (retval)
			goto done;
		retval = ext2fs_extent_fix_parents(handle);
		if (retval)
			goto done;
	} else {
		__u32	save_length;
		blk64_t	save_lblk;
		struct ext2fs_extent save_extent;
		errcode_t r2;

#ifdef DEBUG
		printf("(re/un)mapping in middle of extent\n");
#endif
		/* need to split this extent; later */
		save_lblk = extent.e_lblk;
		save_length = extent.e_len;
		save_extent = extent;

		/* shorten pre-split extent */
		extent.e_len = (logical - extent.e_lblk);
		retval = ext2fs_extent_replace(handle, 0, &extent);
		if (retval)
			goto done;
		/* insert our new extent, if any */
		if (physical) {
			/* insert new extent after current */
			retval = ext2fs_extent_insert(handle,
					EXT2_EXTENT_INSERT_AFTER, &newextent);
			if (retval) {
				r2 = ext2fs_extent_goto(handle, save_lblk);
				if (r2 == 0)
					(void)ext2fs_extent_replace(handle, 0,
							      &save_extent);
				goto done;
			}
		}
		/* add post-split extent */
		extent.e_pblk += extent.e_len + 1;
		extent.e_lblk += extent.e_len + 1;
		extent.e_len = save_length - extent.e_len - 1;
		retval = ext2fs_extent_insert(handle,
				EXT2_EXTENT_INSERT_AFTER, &extent);
		if (retval) {
			if (physical) {
				r2 = ext2fs_extent_goto(handle,
							newextent.e_lblk);
				if (r2 == 0)
					(void)ext2fs_extent_delete(handle, 0);
			}
			r2 = ext2fs_extent_goto(handle, save_lblk);
			if (r2 == 0)
				(void)ext2fs_extent_replace(handle, 0,
							    &save_extent);
			goto done;
		}
	}

done:
	/* get handle back to its position */
	if (orig_height > handle->max_depth)
		orig_height = handle->max_depth; /* In case we shortened the tree */
	ext2fs_extent_goto2(handle, orig_height, orig_lblk);
	return retval;
}