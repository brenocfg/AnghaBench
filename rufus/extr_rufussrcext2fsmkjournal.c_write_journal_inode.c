#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {scalar_t__ i_blocks; int i_links_count; int i_mode; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_size_high; int /*<<< orphan*/  i_block; scalar_t__ i_ctime; scalar_t__ i_mtime; int /*<<< orphan*/  i_flags; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  unsigned long long blk_t ;
typedef  unsigned long long blk64_t ;
struct TYPE_14__ {int /*<<< orphan*/  s_jnl_backup_type; int /*<<< orphan*/ * s_jnl_blocks; } ;
struct TYPE_13__ {TYPE_9__* super; int /*<<< orphan*/  io; scalar_t__ now; scalar_t__ blocksize; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int EXT2_FALLOCATE_FORCE_INIT ; 
 int EXT2_FALLOCATE_ZERO_BLOCKS ; 
 int EXT2_MKJOURNAL_LAZYINIT ; 
 int EXT2_N_BLOCKS ; 
 int /*<<< orphan*/  EXT3_JNL_BACKUP_BLOCKS ; 
 int /*<<< orphan*/  EXT4_EXTENTS_FL ; 
 int LINUX_S_IFREG ; 
 scalar_t__ ext2fs_bmap2 (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 scalar_t__ ext2fs_create_journal_superblock (TYPE_1__*,unsigned long long,int,char**) ; 
 scalar_t__ ext2fs_fallocate (TYPE_1__*,int,int /*<<< orphan*/ ,struct ext2_inode*,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_has_feature_extents (TYPE_9__*) ; 
 scalar_t__ ext2fs_inode_size_set (TYPE_1__*,struct ext2_inode*,unsigned long long) ; 
 int /*<<< orphan*/  ext2fs_mark_super_dirty (TYPE_1__*) ; 
 scalar_t__ ext2fs_read_bitmaps (TYPE_1__*) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_new_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 unsigned long long get_midpoint_journal_block (TYPE_1__*) ; 
 scalar_t__ io_channel_write_blk64 (int /*<<< orphan*/ ,unsigned long long,int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errcode_t write_journal_inode(ext2_filsys fs, ext2_ino_t journal_ino,
				     blk_t num_blocks, blk64_t goal, int flags)
{
	char			*buf;
	errcode_t		retval;
	struct ext2_inode	inode;
	unsigned long long	inode_size;
	int			falloc_flags = EXT2_FALLOCATE_FORCE_INIT;
	blk64_t			zblk;

	if ((retval = ext2fs_create_journal_superblock(fs, num_blocks, flags,
						       &buf)))
		return retval;

	if ((retval = ext2fs_read_bitmaps(fs)))
		goto out2;

	if ((retval = ext2fs_read_inode(fs, journal_ino, &inode)))
		goto out2;

	if (inode.i_blocks > 0) {
		retval = EEXIST;
		goto out2;
	}

	if (goal == ~0ULL)
		goal = get_midpoint_journal_block(fs);

	if (ext2fs_has_feature_extents(fs->super))
		inode.i_flags |= EXT4_EXTENTS_FL;

	if (!(flags & EXT2_MKJOURNAL_LAZYINIT))
		falloc_flags |= EXT2_FALLOCATE_ZERO_BLOCKS;

	inode_size = (unsigned long long)fs->blocksize * num_blocks;
	inode.i_mtime = inode.i_ctime = fs->now ? fs->now : time(0);
	inode.i_links_count = 1;
	inode.i_mode = LINUX_S_IFREG | 0600;
	retval = ext2fs_inode_size_set(fs, &inode, inode_size);
	if (retval)
		goto out2;

	retval = ext2fs_fallocate(fs, falloc_flags, journal_ino,
				  &inode, goal, 0, num_blocks);
	if (retval)
		goto out2;

	if ((retval = ext2fs_write_new_inode(fs, journal_ino, &inode)))
		goto out2;

	retval = ext2fs_bmap2(fs, journal_ino, &inode, NULL, 0, 0, NULL, &zblk);
	if (retval)
		goto out2;

	retval = io_channel_write_blk64(fs->io, zblk, 1, buf);
	if (retval)
		goto out2;

	memcpy(fs->super->s_jnl_blocks, inode.i_block, EXT2_N_BLOCKS*4);
	fs->super->s_jnl_blocks[15] = inode.i_size_high;
	fs->super->s_jnl_blocks[16] = inode.i_size;
	fs->super->s_jnl_backup_type = EXT3_JNL_BACKUP_BLOCKS;
	ext2fs_mark_super_dirty(fs);

out2:
	ext2fs_free_mem(&buf);
	return retval;
}