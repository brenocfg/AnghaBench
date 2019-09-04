#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ext2_inode {int i_mode; int i_links_count; scalar_t__ i_size; int /*<<< orphan*/  i_flags; } ;
typedef  int /*<<< orphan*/  inode ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  csum_seed; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FILE_WRITE ; 
 int /*<<< orphan*/  EXT4_EA_INODE_FL ; 
 int /*<<< orphan*/  EXT4_EXTENTS_FL ; 
 int LINUX_S_IFREG ; 
 int /*<<< orphan*/  ext2fs_crc32c_le (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  ext2fs_file_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_file_open (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_file_write (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_has_feature_extents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_inode_alloc_stats2 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_new_inode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_set_ea_inode_hash (struct ext2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_set_ea_inode_ref (struct ext2_inode*,int) ; 
 scalar_t__ ext2fs_write_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 scalar_t__ ext2fs_write_new_inode (TYPE_1__*,int /*<<< orphan*/ ,struct ext2_inode*) ; 
 int /*<<< orphan*/  memset (struct ext2_inode*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static errcode_t xattr_create_ea_inode(ext2_filsys fs, const void *value,
				       size_t value_len, ext2_ino_t *ea_ino)
{
	struct ext2_inode inode;
	ext2_ino_t ino;
	ext2_file_t file;
	__u32 hash;
	errcode_t ret;

	ret = ext2fs_new_inode(fs, 0, 0, 0, &ino);
	if (ret)
		return ret;

	memset(&inode, 0, sizeof(inode));
	inode.i_flags |= EXT4_EA_INODE_FL;
	if (ext2fs_has_feature_extents(fs->super))
		inode.i_flags |= EXT4_EXTENTS_FL;
	inode.i_size = 0;
	inode.i_mode = LINUX_S_IFREG | 0600;
	inode.i_links_count = 1;
	ret = ext2fs_write_new_inode(fs, ino, &inode);
	if (ret)
		return ret;
	/*
	 * ref_count and hash utilize inode's i_*time fields.
	 * ext2fs_write_new_inode() call above initializes these fields with
	 * current time. That's why ref count and hash updates are done
	 * separately below.
	 */
	ext2fs_set_ea_inode_ref(&inode, 1);
	hash = ext2fs_crc32c_le(fs->csum_seed, value, value_len);
	ext2fs_set_ea_inode_hash(&inode, hash);

	ret = ext2fs_write_inode(fs, ino, &inode);
	if (ret)
		return ret;

	ret = ext2fs_file_open(fs, ino, EXT2_FILE_WRITE, &file);
	if (ret)
		return ret;
	ret = ext2fs_file_write(file, value, value_len, NULL);
	ext2fs_file_close(file);
	if (ret)
		return ret;

	ext2fs_inode_alloc_stats2(fs, ino, 1 /* inuse */, 0 /* isdir */);

	*ea_ino = ino;
	return 0;
}