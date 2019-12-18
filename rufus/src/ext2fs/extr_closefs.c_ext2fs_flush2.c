#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct opaque_ext2_group_desc {unsigned long s_state; int s_first_meta_bg; int /*<<< orphan*/  s_feature_incompat; scalar_t__ s_block_group_nr; scalar_t__ s_wtime; } ;
struct ext2fs_numeric_progress_struct {int dummy; } ;
struct ext2_super_block {unsigned long s_state; int s_first_meta_bg; int /*<<< orphan*/  s_feature_incompat; scalar_t__ s_block_group_nr; scalar_t__ s_wtime; } ;
struct ext2_group_desc {int dummy; } ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ dgrp_t ;
typedef  int blk64_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_16__ {size_t desc_blocks; int blocksize; scalar_t__ group_desc_count; int flags; struct opaque_ext2_group_desc* super; int /*<<< orphan*/  io; TYPE_1__* progress_ops; struct opaque_ext2_group_desc* group_desc; scalar_t__ (* write_bitmaps ) (TYPE_2__*) ;scalar_t__ now; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* close ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,scalar_t__) ;int /*<<< orphan*/  (* init ) (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_DESC_PER_BLOCK (struct opaque_ext2_group_desc*) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_ET_NO_MEMORY ; 
 int EXT2_FLAG_DIRTY ; 
 int EXT2_FLAG_FLUSH_NO_SYNC ; 
 int EXT2_FLAG_MASTER_SB_ONLY ; 
 int EXT2_FLAG_SUPER_ONLY ; 
 unsigned long EXT2_VALID_FS ; 
 int /*<<< orphan*/  SUPERBLOCK_SIZE ; 
 int /*<<< orphan*/  ext2fs_clear_feature_journal_needs_recovery (struct opaque_ext2_group_desc*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (struct opaque_ext2_group_desc**) ; 
 scalar_t__ ext2fs_get_array (size_t,int,struct opaque_ext2_group_desc**) ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,struct opaque_ext2_group_desc**) ; 
 struct ext2_group_desc* ext2fs_group_desc (TYPE_2__*,struct opaque_ext2_group_desc*,scalar_t__) ; 
 scalar_t__ ext2fs_has_feature_journal_dev (struct opaque_ext2_group_desc*) ; 
 scalar_t__ ext2fs_has_feature_meta_bg (struct opaque_ext2_group_desc*) ; 
 int /*<<< orphan*/  ext2fs_super_and_bgd_loc2 (TYPE_2__*,scalar_t__,int*,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_superblock_csum_set (TYPE_2__*,struct opaque_ext2_group_desc*) ; 
 int /*<<< orphan*/  ext2fs_swap_group_desc2 (TYPE_2__*,struct ext2_group_desc*) ; 
 int /*<<< orphan*/  ext2fs_swap_super (struct opaque_ext2_group_desc*) ; 
 scalar_t__ io_channel_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  memcpy (struct opaque_ext2_group_desc*,struct opaque_ext2_group_desc*,size_t) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,struct ext2fs_numeric_progress_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ write_backup_super (TYPE_2__*,scalar_t__,int,struct opaque_ext2_group_desc*) ; 
 scalar_t__ write_primary_superblock (TYPE_2__*,struct opaque_ext2_group_desc*) ; 

errcode_t ext2fs_flush2(ext2_filsys fs, int flags)
{
	dgrp_t		i;
	errcode_t	retval;
	unsigned long	fs_state;
	__u32		feature_incompat;
	struct ext2_super_block *super_shadow = 0;
	struct opaque_ext2_group_desc *group_shadow = 0;
#ifdef WORDS_BIGENDIAN
	struct ext2_group_desc *gdp;
	dgrp_t		j;
#endif
	char	*group_ptr;
	blk64_t	old_desc_blocks;
	struct ext2fs_numeric_progress_struct progress;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	fs_state = fs->super->s_state;
	feature_incompat = fs->super->s_feature_incompat;

	fs->super->s_wtime = fs->now ? fs->now : time(NULL);
	fs->super->s_block_group_nr = 0;

	/*
	 * If the write_bitmaps() function is present, call it to
	 * flush the bitmaps.  This is done this way so that a simple
	 * program that doesn't mess with the bitmaps doesn't need to
	 * drag in the bitmaps.c code.
	 *
	 * Bitmap checksums live in the group descriptor, so the
	 * bitmaps need to be written before the descriptors.
	 */
	if (fs->write_bitmaps) {
		retval = fs->write_bitmaps(fs);
		if (retval)
			goto errout;
	}

	/*
	 * Set the state of the FS to be non-valid.  (The state has
	 * already been backed up earlier, and will be restored after
	 * we write out the backup superblocks.)
	 */
	fs->super->s_state &= ~EXT2_VALID_FS;
	ext2fs_clear_feature_journal_needs_recovery(fs->super);

	/* Byte swap the superblock and the group descriptors if necessary */
#ifdef WORDS_BIGENDIAN
	retval = EXT2_ET_NO_MEMORY;
	retval = ext2fs_get_mem(SUPERBLOCK_SIZE, &super_shadow);
	if (retval)
		goto errout;
	retval = ext2fs_get_array(fs->desc_blocks, fs->blocksize,
				  &group_shadow);
	if (retval)
		goto errout;
	memcpy(super_shadow, fs->super, sizeof(struct ext2_super_block));
	memcpy(group_shadow, fs->group_desc, (size_t) fs->blocksize *
	       fs->desc_blocks);

	ext2fs_swap_super(super_shadow);
	for (j = 0; j < fs->group_desc_count; j++) {
		gdp = ext2fs_group_desc(fs, group_shadow, j);
		ext2fs_swap_group_desc2(fs, gdp);
	}
#else
	super_shadow = fs->super;
	group_shadow = fs->group_desc;
#endif

	/*
	 * If this is an external journal device, don't write out the
	 * block group descriptors or any of the backup superblocks
	 */
	if (ext2fs_has_feature_journal_dev(fs->super))
		goto write_primary_superblock_only;

	/*
	 * Write out the master group descriptors, and the backup
	 * superblocks and group descriptors.
	 */
	group_ptr = (char *) group_shadow;
	if (ext2fs_has_feature_meta_bg(fs->super)) {
		old_desc_blocks = fs->super->s_first_meta_bg;
		if (old_desc_blocks > fs->desc_blocks)
			old_desc_blocks = fs->desc_blocks;
	} else
		old_desc_blocks = fs->desc_blocks;

	if (fs->progress_ops && fs->progress_ops->init)
		(fs->progress_ops->init)(fs, &progress, NULL,
					 fs->group_desc_count);


	for (i = 0; i < fs->group_desc_count; i++) {
		blk64_t	super_blk, old_desc_blk, new_desc_blk;

		if (fs->progress_ops && fs->progress_ops->update)
			(fs->progress_ops->update)(fs, &progress, i);
		ext2fs_super_and_bgd_loc2(fs, i, &super_blk, &old_desc_blk,
					 &new_desc_blk, 0);

		if (!(fs->flags & EXT2_FLAG_MASTER_SB_ONLY) &&i && super_blk) {
			retval = write_backup_super(fs, i, super_blk,
						    super_shadow);
			if (retval)
				goto errout;
		}
		if (fs->flags & EXT2_FLAG_SUPER_ONLY)
			continue;
		if ((old_desc_blk) &&
		    (!(fs->flags & EXT2_FLAG_MASTER_SB_ONLY) || (i == 0))) {
			retval = io_channel_write_blk64(fs->io,
			      old_desc_blk, old_desc_blocks, group_ptr);
			if (retval)
				goto errout;
		}
		if (new_desc_blk) {
			int meta_bg = i / EXT2_DESC_PER_BLOCK(fs->super);

			retval = io_channel_write_blk64(fs->io, new_desc_blk,
				1, group_ptr + (meta_bg*fs->blocksize));
			if (retval)
				goto errout;
		}
	}

	if (fs->progress_ops && fs->progress_ops->close)
		(fs->progress_ops->close)(fs, &progress, NULL);

write_primary_superblock_only:
	/*
	 * Write out master superblock.  This has to be done
	 * separately, since it is located at a fixed location
	 * (SUPERBLOCK_OFFSET).  We flush all other pending changes
	 * out to disk first, just to avoid a race condition with an
	 * insy-tinsy window....
	 */

	fs->super->s_block_group_nr = 0;
	fs->super->s_state = fs_state;
	fs->super->s_feature_incompat = feature_incompat;
#ifdef WORDS_BIGENDIAN
	*super_shadow = *fs->super;
	ext2fs_swap_super(super_shadow);
#endif

	retval = ext2fs_superblock_csum_set(fs, super_shadow);
	if (retval)
		return retval;

	if (!(flags & EXT2_FLAG_FLUSH_NO_SYNC)) {
		retval = io_channel_flush(fs->io);
		if (retval)
			goto errout;
	}
	retval = write_primary_superblock(fs, super_shadow);
	if (retval)
		goto errout;

	fs->flags &= ~EXT2_FLAG_DIRTY;

	if (!(flags & EXT2_FLAG_FLUSH_NO_SYNC)) {
		retval = io_channel_flush(fs->io);
		if (retval)
			goto errout;
	}
errout:
	fs->super->s_state = fs_state;
#ifdef WORDS_BIGENDIAN
	if (super_shadow)
		ext2fs_free_mem(&super_shadow);
	if (group_shadow)
		ext2fs_free_mem(&group_shadow);
#endif
	return retval;
}