#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
typedef  unsigned int ext2_ino_t ;
typedef  TYPE_2__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ dgrp_t ;
typedef  unsigned int blk64_t ;
struct TYPE_21__ {unsigned int blocksize; char* block_map; char* inode_map; int flags; scalar_t__ group_desc_count; int /*<<< orphan*/  io; int /*<<< orphan*/  image_io; TYPE_14__* super; TYPE_1__* image_header; int /*<<< orphan*/  device_name; int /*<<< orphan*/  write_bitmaps; } ;
struct TYPE_20__ {int /*<<< orphan*/  offset_blockmap; int /*<<< orphan*/  offset_inodemap; } ;
struct TYPE_19__ {unsigned int s_inodes_count; int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 unsigned int EXT2FS_B2C (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT2_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int EXT2_CLUSTERS_PER_GROUP (TYPE_14__*) ; 
 scalar_t__ EXT2_ET_BLOCK_BITMAP_CSUM_INVALID ; 
 scalar_t__ EXT2_ET_BLOCK_BITMAP_READ ; 
 scalar_t__ EXT2_ET_CORRUPT_SUPERBLOCK ; 
 scalar_t__ EXT2_ET_INODE_BITMAP_CSUM_INVALID ; 
 scalar_t__ EXT2_ET_INODE_BITMAP_READ ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int EXT2_FLAG_IGNORE_CSUM_ERRORS ; 
 int EXT2_FLAG_IMAGE_FILE ; 
 unsigned int EXT2_GROUPS_TO_CLUSTERS (TYPE_14__*,scalar_t__) ; 
 int EXT2_INODES_PER_GROUP (TYPE_14__*) ; 
 scalar_t__ ext2fs_allocate_block_bitmap (TYPE_2__*,char*,char**) ; 
 scalar_t__ ext2fs_allocate_inode_bitmap (TYPE_2__*,char*,char**) ; 
 scalar_t__ ext2fs_bg_flags_test (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_block_bitmap_csum_verify (TYPE_2__*,scalar_t__,char*,int) ; 
 unsigned int ext2fs_block_bitmap_loc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ext2fs_free_block_bitmap (char*) ; 
 int /*<<< orphan*/  ext2fs_free_inode_bitmap (char*) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_mem (scalar_t__,char**) ; 
 scalar_t__ ext2fs_group_desc_csum_verify (TYPE_2__*,scalar_t__) ; 
 int ext2fs_has_group_desc_csum (TYPE_2__*) ; 
 int /*<<< orphan*/  ext2fs_inode_bitmap_csum_verify (TYPE_2__*,scalar_t__,char*,int) ; 
 unsigned int ext2fs_inode_bitmap_loc (TYPE_2__*,scalar_t__) ; 
 unsigned int ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_set_block_bitmap_range2 (char*,unsigned int,unsigned int,char*) ; 
 scalar_t__ ext2fs_set_inode_bitmap_range2 (char*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  ext2fs_write_bitmaps ; 
 scalar_t__ io_channel_alloc_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ io_channel_read_blk64 (int /*<<< orphan*/ ,unsigned int,int,char*) ; 
 scalar_t__ mark_uninit_bg_group_blocks (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errcode_t read_bitmaps(ext2_filsys fs, int do_inode, int do_block)
{
	dgrp_t i;
	char *block_bitmap = 0, *inode_bitmap = 0;
	char *buf;
	errcode_t retval;
	int block_nbytes = EXT2_CLUSTERS_PER_GROUP(fs->super) / 8;
	int inode_nbytes = EXT2_INODES_PER_GROUP(fs->super) / 8;
	int csum_flag;
	unsigned int	cnt;
	blk64_t	blk;
	blk64_t	blk_itr = EXT2FS_B2C(fs, fs->super->s_first_data_block);
	blk64_t   blk_cnt;
	ext2_ino_t ino_itr = 1;
	ext2_ino_t ino_cnt;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if ((block_nbytes > (int) fs->blocksize) ||
	    (inode_nbytes > (int) fs->blocksize))
		return EXT2_ET_CORRUPT_SUPERBLOCK;

	fs->write_bitmaps = ext2fs_write_bitmaps;

	csum_flag = ext2fs_has_group_desc_csum(fs);

	retval = ext2fs_get_mem(strlen(fs->device_name) + 80, &buf);
	if (retval)
		return retval;
	if (do_block) {
		if (fs->block_map)
			ext2fs_free_block_bitmap(fs->block_map);
		strcpy(buf, "block bitmap for ");
		strcat(buf, fs->device_name);
		retval = ext2fs_allocate_block_bitmap(fs, buf, &fs->block_map);
		if (retval)
			goto cleanup;
		retval = io_channel_alloc_buf(fs->io, 0, &block_bitmap);
		if (retval)
			goto cleanup;
	} else
		block_nbytes = 0;
	if (do_inode) {
		if (fs->inode_map)
			ext2fs_free_inode_bitmap(fs->inode_map);
		strcpy(buf, "inode bitmap for ");
		strcat(buf, fs->device_name);
		retval = ext2fs_allocate_inode_bitmap(fs, buf, &fs->inode_map);
		if (retval)
			goto cleanup;
		retval = io_channel_alloc_buf(fs->io, 0, &inode_bitmap);
		if (retval)
			goto cleanup;
	} else
		inode_nbytes = 0;
	ext2fs_free_mem(&buf);

	if (fs->flags & EXT2_FLAG_IMAGE_FILE) {
		blk = (ext2fs_le32_to_cpu(fs->image_header->offset_inodemap) / fs->blocksize);
		ino_cnt = fs->super->s_inodes_count;
		while (inode_bitmap && ino_cnt > 0) {
			retval = io_channel_read_blk64(fs->image_io, blk++,
						     1, inode_bitmap);
			if (retval)
				goto cleanup;
			cnt = fs->blocksize << 3;
			if (cnt > ino_cnt)
				cnt = ino_cnt;
			retval = ext2fs_set_inode_bitmap_range2(fs->inode_map,
					       ino_itr, cnt, inode_bitmap);
			if (retval)
				goto cleanup;
			ino_itr += cnt;
			ino_cnt -= cnt;
		}
		blk = (ext2fs_le32_to_cpu(fs->image_header->offset_blockmap) /
		       fs->blocksize);
		blk_cnt = EXT2_GROUPS_TO_CLUSTERS(fs->super,
						  fs->group_desc_count);
		while (block_bitmap && blk_cnt > 0) {
			retval = io_channel_read_blk64(fs->image_io, blk++,
						     1, block_bitmap);
			if (retval)
				goto cleanup;
			cnt = fs->blocksize << 3;
			if (cnt > blk_cnt)
				cnt = blk_cnt;
			retval = ext2fs_set_block_bitmap_range2(fs->block_map,
				       blk_itr, cnt, block_bitmap);
			if (retval)
				goto cleanup;
			blk_itr += cnt;
			blk_cnt -= cnt;
		}
		goto success_cleanup;
	}

	for (i = 0; i < fs->group_desc_count; i++) {
		if (block_bitmap) {
			blk = ext2fs_block_bitmap_loc(fs, i);
			if (csum_flag &&
			    ext2fs_bg_flags_test(fs, i, EXT2_BG_BLOCK_UNINIT) &&
			    ext2fs_group_desc_csum_verify(fs, i))
				blk = 0;
			if (blk) {
				retval = io_channel_read_blk64(fs->io, blk,
							       1, block_bitmap);
				if (retval) {
					retval = EXT2_ET_BLOCK_BITMAP_READ;
					goto cleanup;
				}
				/* verify block bitmap checksum */
				if (!(fs->flags &
				      EXT2_FLAG_IGNORE_CSUM_ERRORS) &&
				    !ext2fs_block_bitmap_csum_verify(fs, i,
						block_bitmap, block_nbytes)) {
					retval =
					EXT2_ET_BLOCK_BITMAP_CSUM_INVALID;
					goto cleanup;
				}
			} else
				memset(block_bitmap, 0, block_nbytes);
			cnt = block_nbytes << 3;
			retval = ext2fs_set_block_bitmap_range2(fs->block_map,
					       blk_itr, cnt, block_bitmap);
			if (retval)
				goto cleanup;
			blk_itr += block_nbytes << 3;
		}
		if (inode_bitmap) {
			blk = ext2fs_inode_bitmap_loc(fs, i);
			if (csum_flag &&
			    ext2fs_bg_flags_test(fs, i, EXT2_BG_INODE_UNINIT) &&
			    ext2fs_group_desc_csum_verify(fs, i))
				blk = 0;
			if (blk) {
				retval = io_channel_read_blk64(fs->io, blk,
							       1, inode_bitmap);
				if (retval) {
					retval = EXT2_ET_INODE_BITMAP_READ;
					goto cleanup;
				}

				/* verify inode bitmap checksum */
				if (!(fs->flags &
				      EXT2_FLAG_IGNORE_CSUM_ERRORS) &&
				    !ext2fs_inode_bitmap_csum_verify(fs, i,
						inode_bitmap, inode_nbytes)) {
					retval =
					EXT2_ET_INODE_BITMAP_CSUM_INVALID;
					goto cleanup;
				}
			} else
				memset(inode_bitmap, 0, inode_nbytes);
			cnt = inode_nbytes << 3;
			retval = ext2fs_set_inode_bitmap_range2(fs->inode_map,
					       ino_itr, cnt, inode_bitmap);
			if (retval)
				goto cleanup;
			ino_itr += inode_nbytes << 3;
		}
	}

	/* Mark group blocks for any BLOCK_UNINIT groups */
	if (do_block) {
		retval = mark_uninit_bg_group_blocks(fs);
		if (retval)
			goto cleanup;
	}

success_cleanup:
	if (inode_bitmap)
		ext2fs_free_mem(&inode_bitmap);
	if (block_bitmap)
		ext2fs_free_mem(&block_bitmap);
	return 0;

cleanup:
	if (do_block) {
		ext2fs_free_mem(&fs->block_map);
		fs->block_map = 0;
	}
	if (do_inode) {
		ext2fs_free_mem(&fs->inode_map);
		fs->inode_map = 0;
	}
	if (inode_bitmap)
		ext2fs_free_mem(&inode_bitmap);
	if (block_bitmap)
		ext2fs_free_mem(&block_bitmap);
	if (buf)
		ext2fs_free_mem(&buf);
	return retval;
}