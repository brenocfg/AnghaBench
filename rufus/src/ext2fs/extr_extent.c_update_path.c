#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ext3_extent_idx {int /*<<< orphan*/  ei_leaf_hi; int /*<<< orphan*/  ei_leaf; } ;
struct ext3_extent_header {int dummy; } ;
typedef  TYPE_2__* ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ blk64_t ;
typedef  int __u64 ;
struct TYPE_8__ {int /*<<< orphan*/  io; } ;
struct TYPE_7__ {int level; TYPE_1__* path; TYPE_4__* fs; int /*<<< orphan*/  ino; int /*<<< orphan*/  inode; } ;
struct TYPE_6__ {scalar_t__ buf; struct ext3_extent_idx* curr; } ;

/* Variables and functions */
 scalar_t__ ext2fs_extent_block_csum_set (TYPE_4__*,int /*<<< orphan*/ ,struct ext3_extent_header*) ; 
 scalar_t__ ext2fs_le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_write_inode (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static errcode_t update_path(ext2_extent_handle_t handle)
{
	blk64_t				blk;
	errcode_t			retval;
	struct ext3_extent_idx		*ix;
	struct ext3_extent_header	*eh;

	if (handle->level == 0) {
		retval = ext2fs_write_inode(handle->fs, handle->ino,
					    handle->inode);
	} else {
		ix = handle->path[handle->level - 1].curr;
		blk = ext2fs_le32_to_cpu(ix->ei_leaf) +
			((__u64) ext2fs_le16_to_cpu(ix->ei_leaf_hi) << 32);

		/* then update the checksum */
		eh = (struct ext3_extent_header *)
				handle->path[handle->level].buf;
		retval = ext2fs_extent_block_csum_set(handle->fs, handle->ino,
						      eh);
		if (retval)
			return retval;

		retval = io_channel_write_blk64(handle->fs->io,
				      blk, 1, handle->path[handle->level].buf);
	}
	return retval;
}