#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct extent_path {int dummy; } ;
struct ext3_extent_header {void* eh_max; void* eh_entries; void* eh_magic; void* eh_depth; } ;
struct ext3_extent {int dummy; } ;
struct ext2_inode {int i_flags; scalar_t__* i_block; } ;
struct ext2_extent_handle {int max_depth; int max_paths; int /*<<< orphan*/  magic; scalar_t__ level; TYPE_3__* path; struct ext2_inode* inode; void* type; struct ext2_inode inodebuf; TYPE_1__* fs; scalar_t__ ino; } ;
typedef  scalar_t__ ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  struct ext2_extent_handle* ext2_extent_handle_t ;
typedef  scalar_t__ errcode_t ;
struct TYPE_9__ {scalar_t__ s_inodes_count; } ;
struct TYPE_8__ {char* buf; int end_blk; int visit_num; scalar_t__ curr; void* max_entries; void* entries; void* left; } ;
struct TYPE_7__ {int blocksize; TYPE_6__* super; } ;

/* Variables and functions */
 int EXT2_BLOCK_SIZE_BITS (TYPE_6__*) ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_BAD_INODE_NUM ; 
 scalar_t__ EXT2_ET_INODE_NOT_EXTENT ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXTENT_HANDLE ; 
 int EXT2_I_SIZE (struct ext2_inode*) ; 
 int EXT2_N_BLOCKS ; 
 int EXT3_EXT_MAGIC ; 
 int EXT4_EXTENTS_FL ; 
 void* ext2fs_cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ext2fs_extent_free (struct ext2_extent_handle*) ; 
 scalar_t__ ext2fs_extent_header_verify (struct ext3_extent_header*,int) ; 
 scalar_t__ ext2fs_get_mem (int,struct ext2_extent_handle**) ; 
 scalar_t__ ext2fs_get_memzero (int,TYPE_3__**) ; 
 void* ext2fs_le16_to_cpu (void*) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,scalar_t__,struct ext2_inode*) ; 
 int /*<<< orphan*/  memset (struct ext2_extent_handle*,int /*<<< orphan*/ ,int) ; 

errcode_t ext2fs_extent_open2(ext2_filsys fs, ext2_ino_t ino,
				    struct ext2_inode *inode,
				    ext2_extent_handle_t *ret_handle)
{
	struct ext2_extent_handle	*handle;
	errcode_t			retval;
	int				i;
	struct ext3_extent_header	*eh;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (!inode)
		if ((ino == 0) || (ino > fs->super->s_inodes_count))
			return EXT2_ET_BAD_INODE_NUM;

	retval = ext2fs_get_mem(sizeof(struct ext2_extent_handle), &handle);
	if (retval)
		return retval;
	memset(handle, 0, sizeof(struct ext2_extent_handle));

	handle->ino = ino;
	handle->fs = fs;

	if (inode) {
		handle->inode = inode;
	} else {
		handle->inode = &handle->inodebuf;
		retval = ext2fs_read_inode(fs, ino, handle->inode);
		if (retval)
			goto errout;
	}

	eh = (struct ext3_extent_header *) &handle->inode->i_block[0];

	for (i=0; i < EXT2_N_BLOCKS; i++)
		if (handle->inode->i_block[i])
			break;
	if (i >= EXT2_N_BLOCKS) {
		eh->eh_magic = ext2fs_cpu_to_le16(EXT3_EXT_MAGIC);
		eh->eh_depth = 0;
		eh->eh_entries = 0;
		i = (sizeof(handle->inode->i_block) - sizeof(*eh)) /
			sizeof(struct ext3_extent);
		eh->eh_max = ext2fs_cpu_to_le16(i);
		handle->inode->i_flags |= EXT4_EXTENTS_FL;
	}

	if (!(handle->inode->i_flags & EXT4_EXTENTS_FL)) {
		retval = EXT2_ET_INODE_NOT_EXTENT;
		goto errout;
	}

	retval = ext2fs_extent_header_verify(eh, sizeof(handle->inode->i_block));
	if (retval)
		goto errout;

	handle->max_depth = ext2fs_le16_to_cpu(eh->eh_depth);
	handle->type = ext2fs_le16_to_cpu(eh->eh_magic);

	handle->max_paths = handle->max_depth + 1;
	retval = ext2fs_get_memzero(handle->max_paths *
				    sizeof(struct extent_path),
				    &handle->path);
	handle->path[0].buf = (char *) handle->inode->i_block;

	handle->path[0].left = handle->path[0].entries =
		ext2fs_le16_to_cpu(eh->eh_entries);
	handle->path[0].max_entries = ext2fs_le16_to_cpu(eh->eh_max);
	handle->path[0].curr = 0;
	handle->path[0].end_blk =
		(EXT2_I_SIZE(handle->inode) + fs->blocksize - 1) >>
		 EXT2_BLOCK_SIZE_BITS(fs->super);
	handle->path[0].visit_num = 1;
	handle->level = 0;
	handle->magic = EXT2_ET_MAGIC_EXTENT_HANDLE;

	*ret_handle = handle;
	return 0;

errout:
	ext2fs_extent_free(handle);
	return retval;
}