#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int i_mode; int i_links_count; int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_block; int /*<<< orphan*/  i_flags; scalar_t__ i_gid; scalar_t__ i_uid; } ;
typedef  int /*<<< orphan*/  parent_inode ;
typedef  scalar_t__ ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
struct TYPE_20__ {int umask; int /*<<< orphan*/  super; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_DIR_EXISTS ; 
 scalar_t__ EXT2_ET_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ EXT2_FIRST_INO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_FT_DIR ; 
 int /*<<< orphan*/  EXT4_EXTENTS_FL ; 
 int /*<<< orphan*/  EXT4_INLINE_DATA_FL ; 
 int /*<<< orphan*/  EXT4_MIN_INLINE_DATA_SIZE ; 
 int LINUX_S_IFDIR ; 
 int /*<<< orphan*/  ext2fs_block_alloc_stats2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2fs_extent_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_extent_open2 (TYPE_1__*,scalar_t__,struct ext2_inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_extent_set_bmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_find_inode_goal (TYPE_1__*,scalar_t__,struct ext2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_has_feature_extents (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_has_feature_inline_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_iblk_set (TYPE_1__*,struct ext2_inode*,int) ; 
 scalar_t__ ext2fs_inline_data_init (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_inode_alloc_stats2 (TYPE_1__*,scalar_t__,int,int) ; 
 scalar_t__ ext2fs_link (TYPE_1__*,scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_lookup (TYPE_1__*,scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ext2fs_new_block2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_new_dir_block (TYPE_1__*,scalar_t__,scalar_t__,char**) ; 
 scalar_t__ ext2fs_new_dir_inline_data (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_new_inode (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,scalar_t__,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_dir_block4 (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ext2fs_write_inode (TYPE_1__*,scalar_t__,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_new_inode (TYPE_1__*,scalar_t__,struct ext2_inode*) ; 
 int /*<<< orphan*/  memset (struct ext2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

errcode_t ext2fs_mkdir(ext2_filsys fs, ext2_ino_t parent, ext2_ino_t inum,
		       const char *name)
{
	ext2_extent_handle_t	handle;
	errcode_t		retval;
	struct ext2_inode	parent_inode, inode;
	ext2_ino_t		ino = inum;
	ext2_ino_t		scratch_ino;
	blk64_t			blk;
	char			*block = 0;
	int			inline_data = 0;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	/*
	 * Create a new dir with inline data iff this feature is enabled
	 * and ino >= EXT2_FIRST_INO.
	 */
	if ((!ino || ino >= EXT2_FIRST_INO(fs->super)) &&
	    ext2fs_has_feature_inline_data(fs->super))
		inline_data = 1;

	/*
	 * Allocate an inode, if necessary
	 */
	if (!ino) {
		retval = ext2fs_new_inode(fs, parent, LINUX_S_IFDIR | 0755,
					  0, &ino);
		if (retval)
			goto cleanup;
	}

	/*
	 * Allocate a data block for the directory
	 */
	memset(&inode, 0, sizeof(struct ext2_inode));
	if (!inline_data) {
		retval = ext2fs_new_block2(fs, ext2fs_find_inode_goal(fs, ino,
								      &inode,
								      0),
					   NULL, &blk);
		if (retval)
			goto cleanup;
	}

	/*
	 * Create a scratch template for the directory
	 */
	if (inline_data)
		retval = ext2fs_new_dir_inline_data(fs, ino, parent,
						    inode.i_block);
	else
		retval = ext2fs_new_dir_block(fs, ino, parent, &block);
	if (retval)
		goto cleanup;

	/*
	 * Get the parent's inode, if necessary
	 */
	if (parent != ino) {
		retval = ext2fs_read_inode(fs, parent, &parent_inode);
		if (retval)
			goto cleanup;
	} else
		memset(&parent_inode, 0, sizeof(parent_inode));

	/*
	 * Create the inode structure....
	 */
	inode.i_mode = LINUX_S_IFDIR | (0777 & ~fs->umask);
	inode.i_uid = inode.i_gid = 0;
	if (inline_data) {
		inode.i_flags |= EXT4_INLINE_DATA_FL;
		inode.i_size = EXT4_MIN_INLINE_DATA_SIZE;
	} else {
		if (ext2fs_has_feature_extents(fs->super))
			inode.i_flags |= EXT4_EXTENTS_FL;
		else
			inode.i_block[0] = blk;
		inode.i_size = fs->blocksize;
		ext2fs_iblk_set(fs, &inode, 1);
	}
	inode.i_links_count = 2;

	/*
	 * Write out the inode and inode data block.  The inode generation
	 * number is assigned by write_new_inode, which means that the call
	 * to write_dir_block must come after that.
	 */
	retval = ext2fs_write_new_inode(fs, ino, &inode);
	if (retval)
		goto cleanup;
	if (inline_data) {
		/* init "system.data" for new dir */
		retval = ext2fs_inline_data_init(fs, ino);
	} else {
		retval = ext2fs_write_dir_block4(fs, blk, block, 0, ino);
		if (retval)
			goto cleanup;

		if (ext2fs_has_feature_extents(fs->super)) {
			retval = ext2fs_extent_open2(fs, ino, &inode, &handle);
			if (retval)
				goto cleanup;
			retval = ext2fs_extent_set_bmap(handle, 0, blk, 0);
			ext2fs_extent_free(handle);
			if (retval)
				goto cleanup;
		}
	}

	/*
	 * Link the directory into the filesystem hierarchy
	 */
	if (name) {
		retval = ext2fs_lookup(fs, parent, name, strlen(name), 0,
				       &scratch_ino);
		if (!retval) {
			retval = EXT2_ET_DIR_EXISTS;
			name = 0;
			goto cleanup;
		}
		if (retval != EXT2_ET_FILE_NOT_FOUND)
			goto cleanup;
		retval = ext2fs_link(fs, parent, name, ino, EXT2_FT_DIR);
		if (retval)
			goto cleanup;
	}

	/*
	 * Update parent inode's counts
	 */
	if (parent != ino) {
		/* reload parent inode due to inline data */
		retval = ext2fs_read_inode(fs, parent, &parent_inode);
		if (retval)
			goto cleanup;
		parent_inode.i_links_count++;
		retval = ext2fs_write_inode(fs, parent, &parent_inode);
		if (retval)
			goto cleanup;
	}

	/*
	 * Update accounting....
	 */
	if (!inline_data)
		ext2fs_block_alloc_stats2(fs, blk, +1);
	ext2fs_inode_alloc_stats2(fs, ino, +1, 1);

cleanup:
	if (block)
		ext2fs_free_mem(&block);
	return retval;

}