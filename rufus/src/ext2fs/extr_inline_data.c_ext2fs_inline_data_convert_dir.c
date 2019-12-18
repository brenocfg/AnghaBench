#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ext2_dir_entry_tail {int dummy; } ;
struct ext2_dir_entry {char* name; int rec_len; int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 struct ext2_dir_entry_tail* EXT2_DIRENT_TAIL (char*,int) ; 
 int EXT2_DIR_REC_LEN (int) ; 
 int EXT2_FT_DIR ; 
 int EXT4_INLINE_DATA_DOTDOT_SIZE ; 
 int /*<<< orphan*/  ext2fs_dirent_set_file_type (struct ext2_dir_entry*,int) ; 
 int /*<<< orphan*/  ext2fs_dirent_set_name_len (struct ext2_dir_entry*,int) ; 
 scalar_t__ ext2fs_get_rec_len (TYPE_1__*,struct ext2_dir_entry*,unsigned int*) ; 
 scalar_t__ ext2fs_has_feature_filetype (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_initialize_dirent_tail (TYPE_1__*,struct ext2_dir_entry_tail*) ; 
 int /*<<< orphan*/  ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_set_rec_len (TYPE_1__*,unsigned int,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static errcode_t ext2fs_inline_data_convert_dir(ext2_filsys fs, ext2_ino_t ino,
						char *bbuf, char *ibuf, int size)
{
	struct ext2_dir_entry *dir, *dir2;
	struct ext2_dir_entry_tail *t;
	errcode_t retval;
	int offset;
	unsigned int rec_len;
	int csum_size = 0;
	int filetype = 0;

	if (ext2fs_has_feature_metadata_csum(fs->super))
		csum_size = sizeof(struct ext2_dir_entry_tail);

	/* Create '.' and '..' */
	if (ext2fs_has_feature_filetype(fs->super))
		filetype = EXT2_FT_DIR;

	/*
	 * Set up entry for '.'
	 */
	dir = (struct ext2_dir_entry *) bbuf;
	dir->inode = ino;
	ext2fs_dirent_set_name_len(dir, 1);
	ext2fs_dirent_set_file_type(dir, filetype);
	dir->name[0] = '.';
	rec_len = (fs->blocksize - csum_size) - EXT2_DIR_REC_LEN(1);
	dir->rec_len = EXT2_DIR_REC_LEN(1);

	/*
	 * Set up entry for '..'
	 */
	dir = (struct ext2_dir_entry *) (bbuf + dir->rec_len);
	dir->rec_len = EXT2_DIR_REC_LEN(2);
	dir->inode = ext2fs_le32_to_cpu(((__u32 *)ibuf)[0]);
	ext2fs_dirent_set_name_len(dir, 2);
	ext2fs_dirent_set_file_type(dir, filetype);
	dir->name[0] = '.';
	dir->name[1] = '.';

	/*
	 * Adjust the last rec_len
	 */
	offset = EXT2_DIR_REC_LEN(1) + EXT2_DIR_REC_LEN(2);
	dir = (struct ext2_dir_entry *) (bbuf + offset);
	memcpy(bbuf + offset, ibuf + EXT4_INLINE_DATA_DOTDOT_SIZE,
	       size - EXT4_INLINE_DATA_DOTDOT_SIZE);
	size += EXT2_DIR_REC_LEN(1) + EXT2_DIR_REC_LEN(2) -
		EXT4_INLINE_DATA_DOTDOT_SIZE;

	do {
		dir2 = dir;
		retval = ext2fs_get_rec_len(fs, dir, &rec_len);
		if (retval)
			goto err;
		offset += rec_len;
		dir = (struct ext2_dir_entry *) (bbuf + offset);
	} while (offset < size);
	rec_len += fs->blocksize - csum_size - offset;
	retval = ext2fs_set_rec_len(fs, rec_len, dir2);
	if (retval)
		goto err;

	if (csum_size) {
		t = EXT2_DIRENT_TAIL(bbuf, fs->blocksize);
		ext2fs_initialize_dirent_tail(fs, t);
	}

err:
	return retval;
}