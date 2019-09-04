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
struct link_struct {int namelen; scalar_t__ inode; int flags; scalar_t__ done; int /*<<< orphan*/  sb; int /*<<< orphan*/  name; void* err; TYPE_1__* fs; } ;
struct ext2_dir_entry_tail {int dummy; } ;
struct ext2_dir_entry {scalar_t__ inode; int rec_len; char* name; } ;
struct TYPE_4__ {unsigned int blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int DIRENT_ABORT ; 
 int DIRENT_CHANGED ; 
 struct ext2_dir_entry_tail* EXT2_DIRENT_TAIL (char*,unsigned int) ; 
 int EXT2_DIR_REC_LEN (int) ; 
 int ext2fs_dirent_name_len (struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  ext2fs_dirent_set_file_type (struct ext2_dir_entry*,int) ; 
 int /*<<< orphan*/  ext2fs_dirent_set_name_len (struct ext2_dir_entry*,int) ; 
 void* ext2fs_get_rec_len (TYPE_1__*,struct ext2_dir_entry*,unsigned int*) ; 
 scalar_t__ ext2fs_has_feature_filetype (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_initialize_dirent_tail (TYPE_1__*,struct ext2_dir_entry_tail*) ; 
 void* ext2fs_set_rec_len (TYPE_1__*,unsigned int,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int link_proc(struct ext2_dir_entry *dirent,
		     int	offset,
		     int	blocksize,
		     char	*buf,
		     void	*priv_data)
{
	struct link_struct *ls = (struct link_struct *) priv_data;
	struct ext2_dir_entry *next;
	unsigned int rec_len, min_rec_len, curr_rec_len;
	int ret = 0;
	int csum_size = 0;
	struct ext2_dir_entry_tail *t;

	if (ls->done)
		return DIRENT_ABORT;

	rec_len = EXT2_DIR_REC_LEN(ls->namelen);

	ls->err = ext2fs_get_rec_len(ls->fs, dirent, &curr_rec_len);
	if (ls->err)
		return DIRENT_ABORT;

	if (ext2fs_has_feature_metadata_csum(ls->fs->super))
		csum_size = sizeof(struct ext2_dir_entry_tail);
	/*
	 * See if the following directory entry (if any) is unused;
	 * if so, absorb it into this one.
	 */
	next = (struct ext2_dir_entry *) (buf + offset + curr_rec_len);
	if ((offset + (int) curr_rec_len < blocksize - (8 + csum_size)) &&
	    (next->inode == 0) &&
	    (offset + (int) curr_rec_len + (int) next->rec_len <= blocksize)) {
		curr_rec_len += next->rec_len;
		ls->err = ext2fs_set_rec_len(ls->fs, curr_rec_len, dirent);
		if (ls->err)
			return DIRENT_ABORT;
		ret = DIRENT_CHANGED;
	}

	/*
	 * Since ext2fs_link blows away htree data, we need to be
	 * careful -- if metadata_csum is enabled and we're passed in
	 * a dirent that contains htree data, we need to create the
	 * fake entry at the end of the block that hides the checksum.
	 */

	/* De-convert a dx_node block */
	if (csum_size &&
	    curr_rec_len == ls->fs->blocksize &&
	    !dirent->inode) {
		curr_rec_len -= csum_size;
		ls->err = ext2fs_set_rec_len(ls->fs, curr_rec_len, dirent);
		if (ls->err)
			return DIRENT_ABORT;
		t = EXT2_DIRENT_TAIL(buf, ls->fs->blocksize);
		ext2fs_initialize_dirent_tail(ls->fs, t);
		ret = DIRENT_CHANGED;
	}

	/* De-convert a dx_root block */
	if (csum_size &&
	    curr_rec_len == ls->fs->blocksize - EXT2_DIR_REC_LEN(1) &&
	    offset == EXT2_DIR_REC_LEN(1) &&
	    dirent->name[0] == '.' && dirent->name[1] == '.') {
		curr_rec_len -= csum_size;
		ls->err = ext2fs_set_rec_len(ls->fs, curr_rec_len, dirent);
		if (ls->err)
			return DIRENT_ABORT;
		t = EXT2_DIRENT_TAIL(buf, ls->fs->blocksize);
		ext2fs_initialize_dirent_tail(ls->fs, t);
		ret = DIRENT_CHANGED;
	}

	/*
	 * If the directory entry is used, see if we can split the
	 * directory entry to make room for the new name.  If so,
	 * truncate it and return.
	 */
	if (dirent->inode) {
		min_rec_len = EXT2_DIR_REC_LEN(ext2fs_dirent_name_len(dirent));
		if (curr_rec_len < (min_rec_len + rec_len))
			return ret;
		rec_len = curr_rec_len - min_rec_len;
		ls->err = ext2fs_set_rec_len(ls->fs, min_rec_len, dirent);
		if (ls->err)
			return DIRENT_ABORT;
		next = (struct ext2_dir_entry *) (buf + offset +
						  dirent->rec_len);
		next->inode = 0;
		ext2fs_dirent_set_name_len(next, 0);
		ext2fs_dirent_set_file_type(next, 0);
		ls->err = ext2fs_set_rec_len(ls->fs, rec_len, next);
		if (ls->err)
			return DIRENT_ABORT;
		return DIRENT_CHANGED;
	}

	/*
	 * If we get this far, then the directory entry is not used.
	 * See if we can fit the request entry in.  If so, do it.
	 */
	if (curr_rec_len < rec_len)
		return ret;
	dirent->inode = ls->inode;
	ext2fs_dirent_set_name_len(dirent, ls->namelen);
	strncpy(dirent->name, ls->name, ls->namelen);
	if (ext2fs_has_feature_filetype(ls->sb))
		ext2fs_dirent_set_file_type(dirent, ls->flags & 0x7);

	ls->done++;
	return DIRENT_ABORT|DIRENT_CHANGED;
}