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
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_4__ {scalar_t__ magic; scalar_t__ image_io; scalar_t__ io; scalar_t__ block_sha_map; struct TYPE_4__* mmp_cmp; struct TYPE_4__* mmp_buf; scalar_t__ icache; scalar_t__ dblist; scalar_t__ badblocks; struct TYPE_4__* image_header; scalar_t__ inode_map; scalar_t__ block_map; struct TYPE_4__* group_desc; struct TYPE_4__* orig_super; struct TYPE_4__* super; struct TYPE_4__* device_name; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int /*<<< orphan*/  ext2fs_badblocks_list_free (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_block_bitmap (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_dblist (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_inode_bitmap (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_inode_cache (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_1__**) ; 
 int /*<<< orphan*/  ext2fs_hashmap_free (scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_zero_blocks2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_channel_close (scalar_t__) ; 

void ext2fs_free(ext2_filsys fs)
{
	if (!fs || (fs->magic != EXT2_ET_MAGIC_EXT2FS_FILSYS))
		return;
	if (fs->image_io != fs->io) {
		if (fs->image_io)
			io_channel_close(fs->image_io);
	}
	if (fs->io) {
		io_channel_close(fs->io);
	}
	if (fs->device_name)
		ext2fs_free_mem(&fs->device_name);
	if (fs->super)
		ext2fs_free_mem(&fs->super);
	if (fs->orig_super)
		ext2fs_free_mem(&fs->orig_super);
	if (fs->group_desc)
		ext2fs_free_mem(&fs->group_desc);
	if (fs->block_map)
		ext2fs_free_block_bitmap(fs->block_map);
	if (fs->inode_map)
		ext2fs_free_inode_bitmap(fs->inode_map);
	if (fs->image_header)
		ext2fs_free_mem(&fs->image_header);

	if (fs->badblocks)
		ext2fs_badblocks_list_free(fs->badblocks);
	fs->badblocks = 0;

	if (fs->dblist)
		ext2fs_free_dblist(fs->dblist);

	if (fs->icache)
		ext2fs_free_inode_cache(fs->icache);

	if (fs->mmp_buf)
		ext2fs_free_mem(&fs->mmp_buf);
	if (fs->mmp_cmp)
		ext2fs_free_mem(&fs->mmp_cmp);

	if (fs->block_sha_map)
		ext2fs_hashmap_free(fs->block_sha_map);

	fs->magic = 0;

	// coverity[check_return]
	ext2fs_zero_blocks2(NULL, 0, 0, NULL, NULL);
	ext2fs_free_mem(&fs);
}