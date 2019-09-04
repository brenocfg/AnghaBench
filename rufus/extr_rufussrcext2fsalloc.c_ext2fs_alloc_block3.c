#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct blk_alloc_ctx {int dummy; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_9__ {int /*<<< orphan*/  io; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  block_map; scalar_t__ (* get_alloc_block ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* get_alloc_block2 ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct blk_alloc_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_block_alloc_stats2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext2fs_new_block3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct blk_alloc_ctx*) ; 
 scalar_t__ ext2fs_read_block_bitmap (TYPE_1__*) ; 
 scalar_t__ ext2fs_zero_blocks2 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct blk_alloc_ctx*) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errcode_t ext2fs_alloc_block3(ext2_filsys fs, blk64_t goal, char *block_buf,
			      blk64_t *ret, struct blk_alloc_ctx *ctx)
{
	errcode_t	retval;
	blk64_t		block;

	if (fs->get_alloc_block2) {
		retval = (fs->get_alloc_block2)(fs, goal, &block, ctx);
		if (retval)
			goto fail;
	} else if (fs->get_alloc_block) {
		retval = (fs->get_alloc_block)(fs, goal, &block);
		if (retval)
			goto fail;
	} else {
		if (!fs->block_map) {
			retval = ext2fs_read_block_bitmap(fs);
			if (retval)
				goto fail;
		}

		retval = ext2fs_new_block3(fs, goal, 0, &block, ctx);
		if (retval)
			goto fail;
	}

	if (block_buf) {
		memset(block_buf, 0, fs->blocksize);
		retval = io_channel_write_blk64(fs->io, block, 1, block_buf);
	} else
		retval = ext2fs_zero_blocks2(fs, block, 1, NULL, NULL);
	if (retval)
		goto fail;

	ext2fs_block_alloc_stats2(fs, block, +1);
	*ret = block;

fail:
	return retval;
}