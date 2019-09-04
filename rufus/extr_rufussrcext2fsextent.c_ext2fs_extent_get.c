#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct extent_path {scalar_t__ visit_num; scalar_t__ left; int entries; scalar_t__ end_blk; struct ext3_extent_idx* curr; void* max_entries; scalar_t__ buf; } ;
struct ext3_extent_idx {int /*<<< orphan*/  ei_block; int /*<<< orphan*/  ei_leaf_hi; int /*<<< orphan*/  ei_leaf; } ;
struct ext3_extent_header {int /*<<< orphan*/  eh_max; int /*<<< orphan*/  eh_entries; } ;
struct ext3_extent {int /*<<< orphan*/  ee_len; int /*<<< orphan*/  ee_block; int /*<<< orphan*/  ee_start_hi; int /*<<< orphan*/  ee_start; } ;
struct ext2fs_extent {scalar_t__ e_lblk; scalar_t__ e_len; int /*<<< orphan*/  e_flags; void* e_pblk; } ;
typedef  TYPE_1__* ext2_extent_handle_t ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ blk64_t ;
typedef  int __u64 ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  io; int /*<<< orphan*/  image_io; } ;
struct TYPE_5__ {int level; scalar_t__ max_depth; int /*<<< orphan*/  ino; TYPE_3__* fs; struct extent_path* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_EXTENT_CSUM_INVALID ; 
 int /*<<< orphan*/  EXT2_ET_EXTENT_NO_DOWN ; 
 int /*<<< orphan*/  EXT2_ET_EXTENT_NO_NEXT ; 
 int /*<<< orphan*/  EXT2_ET_EXTENT_NO_PREV ; 
 int /*<<< orphan*/  EXT2_ET_EXTENT_NO_UP ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXTENT_HANDLE ; 
 int /*<<< orphan*/  EXT2_ET_NO_CURRENT_NODE ; 
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 
#define  EXT2_EXTENT_CURRENT 136 
#define  EXT2_EXTENT_DOWN 135 
#define  EXT2_EXTENT_DOWN_AND_LAST 134 
#define  EXT2_EXTENT_FIRST_SIB 133 
 int /*<<< orphan*/  EXT2_EXTENT_FLAGS_LEAF ; 
 int /*<<< orphan*/  EXT2_EXTENT_FLAGS_SECOND_VISIT ; 
 int /*<<< orphan*/  EXT2_EXTENT_FLAGS_UNINIT ; 
 int EXT2_EXTENT_LAST_LEAF ; 
#define  EXT2_EXTENT_LAST_SIB 132 
 int EXT2_EXTENT_MOVE_MASK ; 
 int EXT2_EXTENT_NEXT ; 
 int EXT2_EXTENT_NEXT_LEAF ; 
#define  EXT2_EXTENT_NEXT_SIB 131 
 int EXT2_EXTENT_PREV ; 
 int EXT2_EXTENT_PREV_LEAF ; 
#define  EXT2_EXTENT_PREV_SIB 130 
#define  EXT2_EXTENT_ROOT 129 
#define  EXT2_EXTENT_UP 128 
 int EXT2_FLAG_IGNORE_CSUM_ERRORS ; 
 int EXT2_FLAG_IMAGE_FILE ; 
 struct ext3_extent_idx* EXT_FIRST_INDEX (struct ext3_extent_header*) ; 
 scalar_t__ EXT_INIT_MAX_LEN ; 
 struct ext3_extent_idx* EXT_LAST_EXTENT (struct ext3_extent_header*) ; 
 struct ext3_extent_idx* EXT_LAST_INDEX (struct ext3_extent_header*) ; 
 int /*<<< orphan*/  ext2fs_extent_block_csum_verify (TYPE_3__*,int /*<<< orphan*/ ,struct ext3_extent_header*) ; 
 int /*<<< orphan*/  ext2fs_extent_header_verify (struct ext3_extent_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_get_mem (int /*<<< orphan*/ ,scalar_t__*) ; 
 void* ext2fs_le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_channel_read_blk64 (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_extent_get(ext2_extent_handle_t handle,
			    int flags, struct ext2fs_extent *extent)
{
	struct extent_path	*path, *newpath;
	struct ext3_extent_header	*eh;
	struct ext3_extent_idx		*ix = 0;
	struct ext3_extent		*ex;
	errcode_t			retval;
	blk64_t				blk;
	blk64_t				end_blk;
	int				orig_op, op;
	int				failed_csum = 0;

	EXT2_CHECK_MAGIC(handle, EXT2_ET_MAGIC_EXTENT_HANDLE);

	if (!handle->path)
		return EXT2_ET_NO_CURRENT_NODE;

	orig_op = op = flags & EXT2_EXTENT_MOVE_MASK;

retry:
	path = handle->path + handle->level;
	if ((orig_op == EXT2_EXTENT_NEXT) ||
	    (orig_op == EXT2_EXTENT_NEXT_LEAF)) {
		if (handle->level < handle->max_depth) {
			/* interior node */
			if (path->visit_num == 0) {
				path->visit_num++;
				op = EXT2_EXTENT_DOWN;
			} else if (path->left > 0)
				op = EXT2_EXTENT_NEXT_SIB;
			else if (handle->level > 0)
				op = EXT2_EXTENT_UP;
			else
				return EXT2_ET_EXTENT_NO_NEXT;
		} else {
			/* leaf node */
			if (path->left > 0)
				op = EXT2_EXTENT_NEXT_SIB;
			else if (handle->level > 0)
				op = EXT2_EXTENT_UP;
			else
				return EXT2_ET_EXTENT_NO_NEXT;
		}
		if (op != EXT2_EXTENT_NEXT_SIB) {
#ifdef DEBUG_GET_EXTENT
			printf("<<<< OP = %s\n",
			       (op == EXT2_EXTENT_DOWN) ? "down" :
			       ((op == EXT2_EXTENT_UP) ? "up" : "unknown"));
#endif
		}
	}

	if ((orig_op == EXT2_EXTENT_PREV) ||
	    (orig_op == EXT2_EXTENT_PREV_LEAF)) {
		if (handle->level < handle->max_depth) {
			/* interior node */
			if (path->visit_num > 0 ) {
				/* path->visit_num = 0; */
				op = EXT2_EXTENT_DOWN_AND_LAST;
			} else if (path->left < path->entries-1)
				op = EXT2_EXTENT_PREV_SIB;
			else if (handle->level > 0)
				op = EXT2_EXTENT_UP;
			else
				return EXT2_ET_EXTENT_NO_PREV;
		} else {
			/* leaf node */
			if (path->left < path->entries-1)
				op = EXT2_EXTENT_PREV_SIB;
			else if (handle->level > 0)
				op = EXT2_EXTENT_UP;
			else
				return EXT2_ET_EXTENT_NO_PREV;
		}
		if (op != EXT2_EXTENT_PREV_SIB) {
#ifdef DEBUG_GET_EXTENT
			printf("<<<< OP = %s\n",
			       (op == EXT2_EXTENT_DOWN_AND_LAST) ? "down/last" :
			       ((op == EXT2_EXTENT_UP) ? "up" : "unknown"));
#endif
		}
	}

	if (orig_op == EXT2_EXTENT_LAST_LEAF) {
		if ((handle->level < handle->max_depth) &&
		    (path->left == 0))
			op = EXT2_EXTENT_DOWN;
		else
			op = EXT2_EXTENT_LAST_SIB;
#ifdef DEBUG_GET_EXTENT
		printf("<<<< OP = %s\n",
			   (op == EXT2_EXTENT_DOWN) ? "down" : "last_sib");
#endif
	}

	switch (op) {
	case EXT2_EXTENT_CURRENT:
		ix = path->curr;
		break;
	case EXT2_EXTENT_ROOT:
		handle->level = 0;
		path = handle->path + handle->level;
		/* fallthrough */
	case EXT2_EXTENT_FIRST_SIB:
		path->left = path->entries;
		path->curr = 0;
		/* fallthrough */
	case EXT2_EXTENT_NEXT_SIB:
		if (path->left <= 0)
			return EXT2_ET_EXTENT_NO_NEXT;
		if (path->curr) {
			ix = path->curr;
			ix++;
		} else {
			eh = (struct ext3_extent_header *) path->buf;
			ix = EXT_FIRST_INDEX(eh);
		}
		path->left--;
		path->curr = ix;
		path->visit_num = 0;
		break;
	case EXT2_EXTENT_PREV_SIB:
		if (!path->curr ||
		    path->left+1 >= path->entries)
			return EXT2_ET_EXTENT_NO_PREV;
		ix = path->curr;
		ix--;
		path->curr = ix;
		path->left++;
		if (handle->level < handle->max_depth)
			path->visit_num = 1;
		break;
	case EXT2_EXTENT_LAST_SIB:
		eh = (struct ext3_extent_header *) path->buf;
		path->curr = EXT_LAST_EXTENT(eh);
		ix = path->curr;
		path->left = 0;
		path->visit_num = 0;
		break;
	case EXT2_EXTENT_UP:
		if (handle->level <= 0)
			return EXT2_ET_EXTENT_NO_UP;
		handle->level--;
		path--;
		ix = path->curr;
		if ((orig_op == EXT2_EXTENT_PREV) ||
		    (orig_op == EXT2_EXTENT_PREV_LEAF))
			path->visit_num = 0;
		break;
	case EXT2_EXTENT_DOWN:
	case EXT2_EXTENT_DOWN_AND_LAST:
		if (!path->curr ||(handle->level >= handle->max_depth))
			return EXT2_ET_EXTENT_NO_DOWN;

		ix = path->curr;
		newpath = path + 1;
		if (!newpath->buf) {
			retval = ext2fs_get_mem(handle->fs->blocksize,
						&newpath->buf);
			if (retval)
				return retval;
		}
		blk = ext2fs_le32_to_cpu(ix->ei_leaf) +
			((__u64) ext2fs_le16_to_cpu(ix->ei_leaf_hi) << 32);
		if ((handle->fs->flags & EXT2_FLAG_IMAGE_FILE) &&
		    (handle->fs->io != handle->fs->image_io))
			memset(newpath->buf, 0, handle->fs->blocksize);
		else {
			retval = io_channel_read_blk64(handle->fs->io,
						     blk, 1, newpath->buf);
			if (retval)
				return retval;
		}
		handle->level++;

		eh = (struct ext3_extent_header *) newpath->buf;

		retval = ext2fs_extent_header_verify(eh, handle->fs->blocksize);
		if (retval) {
			handle->level--;
			return retval;
		}

		if (!(handle->fs->flags & EXT2_FLAG_IGNORE_CSUM_ERRORS) &&
		    !ext2fs_extent_block_csum_verify(handle->fs, handle->ino,
						     eh))
			failed_csum = 1;

		newpath->left = newpath->entries =
			ext2fs_le16_to_cpu(eh->eh_entries);
		newpath->max_entries = ext2fs_le16_to_cpu(eh->eh_max);

		if (path->left > 0) {
			ix++;
			newpath->end_blk = ext2fs_le32_to_cpu(ix->ei_block);
		} else
			newpath->end_blk = path->end_blk;

		path = newpath;
		if (op == EXT2_EXTENT_DOWN) {
			ix = EXT_FIRST_INDEX((struct ext3_extent_header *) eh);
			path->curr = ix;
			path->left = path->entries - 1;
			path->visit_num = 0;
		} else {
			ix = EXT_LAST_INDEX((struct ext3_extent_header *) eh);
			path->curr = ix;
			path->left = 0;
			if (handle->level < handle->max_depth)
				path->visit_num = 1;
		}
#ifdef DEBUG_GET_EXTENT
		printf("Down to level %d/%d, end_blk=%llu\n",
			   handle->level, handle->max_depth,
			   path->end_blk);
#endif
		break;
	default:
		return EXT2_ET_OP_NOT_SUPPORTED;
	}

	if (!ix)
		return EXT2_ET_NO_CURRENT_NODE;

	extent->e_flags = 0;
#ifdef DEBUG_GET_EXTENT
	printf("(Left %d)\n", path->left);
#endif

	if (handle->level == handle->max_depth) {
		ex = (struct ext3_extent *) ix;

		extent->e_pblk = ext2fs_le32_to_cpu(ex->ee_start) +
			((__u64) ext2fs_le16_to_cpu(ex->ee_start_hi) << 32);
		extent->e_lblk = ext2fs_le32_to_cpu(ex->ee_block);
		extent->e_len = ext2fs_le16_to_cpu(ex->ee_len);
		extent->e_flags |= EXT2_EXTENT_FLAGS_LEAF;
		if (extent->e_len > EXT_INIT_MAX_LEN) {
			extent->e_len -= EXT_INIT_MAX_LEN;
			extent->e_flags |= EXT2_EXTENT_FLAGS_UNINIT;
		}
	} else {
		extent->e_pblk = ext2fs_le32_to_cpu(ix->ei_leaf) +
			((__u64) ext2fs_le16_to_cpu(ix->ei_leaf_hi) << 32);
		extent->e_lblk = ext2fs_le32_to_cpu(ix->ei_block);
		if (path->left > 0) {
			ix++;
			end_blk = ext2fs_le32_to_cpu(ix->ei_block);
		} else
			end_blk = path->end_blk;

		extent->e_len = end_blk - extent->e_lblk;
	}
	if (path->visit_num)
		extent->e_flags |= EXT2_EXTENT_FLAGS_SECOND_VISIT;

	if (((orig_op == EXT2_EXTENT_NEXT_LEAF) ||
	     (orig_op == EXT2_EXTENT_PREV_LEAF)) &&
	    (handle->level != handle->max_depth))
		goto retry;

	if ((orig_op == EXT2_EXTENT_LAST_LEAF) &&
	    ((handle->level != handle->max_depth) ||
	     (path->left != 0)))
		goto retry;

	if (failed_csum)
		return EXT2_ET_EXTENT_CSUM_INVALID;

	return 0;
}