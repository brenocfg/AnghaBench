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
struct ext2fs_extent {int e_lblk; int e_len; int e_pblk; int /*<<< orphan*/  e_flags; } ;
struct ext2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  int blk64_t ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ EXT2_ET_EXTENT_NO_NEXT ; 
 scalar_t__ EXT2_ET_NO_CURRENT_NODE ; 
 int EXT2_EXTENT_CURRENT ; 
 int /*<<< orphan*/  EXT2_EXTENT_INSERT_AFTER ; 
 int EXT2_EXTENT_NEXT_LEAF ; 
 int /*<<< orphan*/  dbg_print_extent (char*,struct ext2fs_extent*) ; 
 int /*<<< orphan*/  dbg_printf (char*,...) ; 
 scalar_t__ ext2fs_extent_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_fix_parents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_extent_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_get (int /*<<< orphan*/ ,int,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_goto (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext2fs_extent_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_extent_open2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_extent_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2fs_extent*) ; 
 scalar_t__ ext2fs_iblk_sub_blocks (int /*<<< orphan*/ ,struct ext2_inode*,int) ; 
 scalar_t__ punch_extent_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*,int,int,int,int*) ; 

__attribute__((used)) static errcode_t ext2fs_punch_extent(ext2_filsys fs, ext2_ino_t ino,
				     struct ext2_inode *inode,
				     blk64_t start, blk64_t end)
{
	ext2_extent_handle_t	handle = 0;
	struct ext2fs_extent	extent;
	errcode_t		retval;
	blk64_t			free_start, next, lfree_start;
	__u32			free_count, newlen;
	int			freed = 0;
	int			op;

	retval = ext2fs_extent_open2(fs, ino, inode, &handle);
	if (retval)
		return retval;
	/*
	 * Find the extent closest to the start of the punch range.  We don't
	 * check the return value because _goto() sets the current node to the
	 * next-lowest extent if 'start' is in a hole, and doesn't set a
	 * current node if there was a real error reading the extent tree.
	 * In that case, _get() will error out.
	 *
	 * Note: If _get() returns 'no current node', that simply means that
	 * there aren't any blocks mapped past this point in the file, so we're
	 * done.
	 */
	retval = ext2fs_extent_goto(handle, start);
	if (retval)
		goto errout;
	retval = ext2fs_extent_get(handle, EXT2_EXTENT_CURRENT, &extent);
	if (retval == EXT2_ET_NO_CURRENT_NODE) {
		retval = 0;
		goto errout;
	} else if (retval)
		goto errout;
	while (1) {
		op = EXT2_EXTENT_NEXT_LEAF;
		dbg_print_extent("main loop", &extent);
		next = extent.e_lblk + extent.e_len;
		dbg_printf("start %llu, end %llu, next %llu\n",
			   (unsigned long long) start,
			   (unsigned long long) end,
			   (unsigned long long) next);
		if (start <= extent.e_lblk) {
			/*
			 * Have we iterated past the end of the punch region?
			 * If so, we can stop.
			 */
			if (end < extent.e_lblk)
				break;
			dbg_printf("Case #%d\n", 1);
			/* Start of deleted region before extent; 
			   adjust beginning of extent */
			free_start = extent.e_pblk;
			lfree_start = extent.e_lblk;
			if (next > end)
				free_count = end - extent.e_lblk + 1;
			else
				free_count = extent.e_len;
			extent.e_len -= free_count;
			extent.e_lblk += free_count;
			extent.e_pblk += free_count;
		} else if (end >= next-1) {
			/*
			 * Is the punch region beyond this extent?  This can
			 * happen if start is already inside a hole.  Try to
			 * advance to the next extent if this is the case.
			 */
			if (start >= next)
				goto next_extent;
			/* End of deleted region after extent;
			   adjust end of extent */
			dbg_printf("Case #%d\n", 2);
			newlen = start - extent.e_lblk;
			free_start = extent.e_pblk + newlen;
			lfree_start = extent.e_lblk + newlen;
			free_count = extent.e_len - newlen;
			extent.e_len = newlen;
		} else {
			struct ext2fs_extent	newex;

			dbg_printf("Case #%d\n", 3);
			/* The hard case; we need to split the extent */
			newex.e_pblk = extent.e_pblk +
				(end + 1 - extent.e_lblk);
			newex.e_lblk = end + 1;
			newex.e_len = next - end - 1;
			newex.e_flags = extent.e_flags;

			extent.e_len = start - extent.e_lblk;
			free_start = extent.e_pblk + extent.e_len;
			lfree_start = extent.e_lblk + extent.e_len;
			free_count = end - start + 1;

			dbg_print_extent("inserting", &newex);
			retval = ext2fs_extent_insert(handle,
					EXT2_EXTENT_INSERT_AFTER, &newex);
			if (retval)
				goto errout;
			retval = ext2fs_extent_fix_parents(handle);
			if (retval)
				goto errout;
			/*
			 * Now pointing at inserted extent; so go back.
			 *
			 * We cannot use EXT2_EXTENT_PREV to go back; note the
			 * subtlety in the comment for fix_parents().
			 */
			retval = ext2fs_extent_goto(handle, extent.e_lblk);
			if (retval)
				goto errout;
		} 
		if (extent.e_len) {
			dbg_print_extent("replacing", &extent);
			retval = ext2fs_extent_replace(handle, 0, &extent);
			if (retval)
				goto errout;
			retval = ext2fs_extent_fix_parents(handle);
		} else {
			struct ext2fs_extent	newex;
			blk64_t			old_lblk, next_lblk;
			dbg_printf("deleting current extent%s\n", "");

			/*
			 * Save the location of the next leaf, then slip
			 * back to the current extent.
			 */
			retval = ext2fs_extent_get(handle, EXT2_EXTENT_CURRENT,
						   &newex);
			if (retval)
				goto errout;
			old_lblk = newex.e_lblk;

			retval = ext2fs_extent_get(handle,
						   EXT2_EXTENT_NEXT_LEAF,
						   &newex);
			if (retval == EXT2_ET_EXTENT_NO_NEXT)
				next_lblk = old_lblk;
			else if (retval)
				goto errout;
			else
				next_lblk = newex.e_lblk;

			retval = ext2fs_extent_goto(handle, old_lblk);
			if (retval)
				goto errout;

			/* Now delete the extent. */
			retval = ext2fs_extent_delete(handle, 0);
			if (retval)
				goto errout;

			retval = ext2fs_extent_fix_parents(handle);
			if (retval && retval != EXT2_ET_NO_CURRENT_NODE)
				goto errout;
			retval = 0;

			/*
			 * Jump forward to the next extent.  If there are
			 * errors, the ext2fs_extent_get down below will
			 * capture them for us.
			 */
			(void)ext2fs_extent_goto(handle, next_lblk);
			op = EXT2_EXTENT_CURRENT;
		}
		if (retval)
			goto errout;
		dbg_printf("Free start %llu, free count = %u\n",
		       free_start, free_count);
		retval = punch_extent_blocks(fs, ino, inode, lfree_start,
					     free_start, free_count, &freed);
		if (retval)
			goto errout;
	next_extent:
		retval = ext2fs_extent_get(handle, op,
					   &extent);
		if (retval == EXT2_ET_EXTENT_NO_NEXT ||
		    retval == EXT2_ET_NO_CURRENT_NODE)
			break;
		if (retval)
			goto errout;
	}
	dbg_printf("Freed %d blocks\n", freed);
	retval = ext2fs_iblk_sub_blocks(fs, inode, freed);
errout:
	ext2fs_extent_free(handle);
	return retval;
}