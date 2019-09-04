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
struct ext2_dir_entry {char* name; int rec_len; void* inode; } ;
typedef  void* ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_6__ {int blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct ext2_dir_entry_tail* EXT2_DIRENT_TAIL (char*,int) ; 
 int EXT2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int EXT2_FT_DIR ; 
 int /*<<< orphan*/  ext2fs_dirent_set_file_type (struct ext2_dir_entry*,int) ; 
 int /*<<< orphan*/  ext2fs_dirent_set_name_len (struct ext2_dir_entry*,int) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_mem (int,char**) ; 
 scalar_t__ ext2fs_has_feature_filetype (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_initialize_dirent_tail (TYPE_1__*,struct ext2_dir_entry_tail*) ; 
 scalar_t__ ext2fs_set_rec_len (TYPE_1__*,int,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

errcode_t ext2fs_new_dir_block(ext2_filsys fs, ext2_ino_t dir_ino,
			       ext2_ino_t parent_ino, char **block)
{
	struct ext2_dir_entry 	*dir = NULL;
	errcode_t		retval;
	char			*buf;
	int			rec_len;
	int			filetype = 0;
	struct ext2_dir_entry_tail	*t;
	int			csum_size = 0;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	retval = ext2fs_get_mem(fs->blocksize, &buf);
	if (retval)
		return retval;
	memset(buf, 0, fs->blocksize);
	dir = (struct ext2_dir_entry *) buf;

	if (ext2fs_has_feature_metadata_csum(fs->super))
		csum_size = sizeof(struct ext2_dir_entry_tail);

	retval = ext2fs_set_rec_len(fs, fs->blocksize - csum_size, dir);
	if (retval) {
		ext2fs_free_mem(&buf);
		return retval;
	}

	if (dir_ino) {
		if (ext2fs_has_feature_filetype(fs->super))
			filetype = EXT2_FT_DIR;
		/*
		 * Set up entry for '.'
		 */
		dir->inode = dir_ino;
		ext2fs_dirent_set_name_len(dir, 1);
		ext2fs_dirent_set_file_type(dir, filetype);
		dir->name[0] = '.';
		rec_len = (fs->blocksize - csum_size) - EXT2_DIR_REC_LEN(1);
		dir->rec_len = EXT2_DIR_REC_LEN(1);

		/*
		 * Set up entry for '..'
		 */
		dir = (struct ext2_dir_entry *) (buf + dir->rec_len);
		retval = ext2fs_set_rec_len(fs, rec_len, dir);
		if (retval) {
			ext2fs_free_mem(&buf);
			return retval;
		}
		dir->inode = parent_ino;
		ext2fs_dirent_set_name_len(dir, 2);
		ext2fs_dirent_set_file_type(dir, filetype);
		dir->name[0] = '.';
		dir->name[1] = '.';

	}

	if (csum_size) {
		t = EXT2_DIRENT_TAIL(buf, fs->blocksize);
		ext2fs_initialize_dirent_tail(fs, t);
	}
	*block = buf;
	return 0;
}