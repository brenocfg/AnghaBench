#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext2fs_extent {scalar_t__ e_lblk; scalar_t__ e_len; } ;
typedef  TYPE_1__* ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;
struct TYPE_4__ {int max_depth; int ino; int level; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_EXTENT_NOT_FOUND ; 
 scalar_t__ EXT2_ET_EXTENT_NO_NEXT ; 
 scalar_t__ EXT2_ET_OP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EXT2_EXTENT_DOWN ; 
 int /*<<< orphan*/  EXT2_EXTENT_NEXT_SIB ; 
 int /*<<< orphan*/  EXT2_EXTENT_PREV_SIB ; 
 int /*<<< orphan*/  EXT2_EXTENT_ROOT ; 
 int /*<<< orphan*/  dbg_print_extent (char*,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_get (TYPE_1__*,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

errcode_t ext2fs_extent_goto2(ext2_extent_handle_t handle,
			      int leaf_level, blk64_t blk)
{
	struct ext2fs_extent	extent;
	errcode_t		retval;

	retval = ext2fs_extent_get(handle, EXT2_EXTENT_ROOT, &extent);
	if (retval) {
		if (retval == EXT2_ET_EXTENT_NO_NEXT)
			retval = EXT2_ET_EXTENT_NOT_FOUND;
		return retval;
	}

	if (leaf_level > handle->max_depth) {
#ifdef DEBUG
		printf("leaf level %d greater than tree depth %d\n",
			leaf_level, handle->max_depth);
#endif
		return EXT2_ET_OP_NOT_SUPPORTED;
	}

#ifdef DEBUG
	printf("goto extent ino %u, level %d, %llu\n", handle->ino,
	       leaf_level, blk);
#endif

#ifdef DEBUG_GOTO_EXTENTS
	dbg_print_extent("root", &extent);
#endif
	while (1) {
		if (handle->max_depth - handle->level == leaf_level) {
			/* block is in this &extent */
			if ((blk >= extent.e_lblk) &&
			    (blk < extent.e_lblk + extent.e_len))
				return 0;
			if (blk < extent.e_lblk) {
				retval = ext2fs_extent_get(handle,
							   EXT2_EXTENT_PREV_SIB,
							   &extent);
				return EXT2_ET_EXTENT_NOT_FOUND;
			}
			retval = ext2fs_extent_get(handle,
						   EXT2_EXTENT_NEXT_SIB,
						   &extent);
			if (retval == EXT2_ET_EXTENT_NO_NEXT)
				return EXT2_ET_EXTENT_NOT_FOUND;
			if (retval)
				return retval;
			continue;
		}

		retval = ext2fs_extent_get(handle, EXT2_EXTENT_NEXT_SIB,
					   &extent);
		if (retval == EXT2_ET_EXTENT_NO_NEXT)
			goto go_down;
		if (retval)
			return retval;

#ifdef DEBUG_GOTO_EXTENTS
		dbg_print_extent("next", &extent);
#endif
		if (blk == extent.e_lblk)
			goto go_down;
		if (blk > extent.e_lblk)
			continue;

		retval = ext2fs_extent_get(handle, EXT2_EXTENT_PREV_SIB,
					   &extent);
		if (retval)
			return retval;

#ifdef DEBUG_GOTO_EXTENTS
		dbg_print_extent("prev", &extent);
#endif

	go_down:
		retval = ext2fs_extent_get(handle, EXT2_EXTENT_DOWN,
					   &extent);
		if (retval)
			return retval;

#ifdef DEBUG_GOTO_EXTENTS
		dbg_print_extent("down", &extent);
#endif
	}
}