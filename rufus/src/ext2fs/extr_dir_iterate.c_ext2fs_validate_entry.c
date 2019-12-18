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
struct ext2_dir_entry {int dummy; } ;
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_4__ {unsigned int blocksize; } ;

/* Variables and functions */
 unsigned int DIRENT_MIN_LENGTH ; 
 int ext2fs_dirent_name_len (struct ext2_dir_entry*) ; 
 scalar_t__ ext2fs_get_rec_len (TYPE_1__*,struct ext2_dir_entry*,unsigned int*) ; 

__attribute__((used)) static int ext2fs_validate_entry(ext2_filsys fs, char *buf,
				 unsigned int offset,
				 unsigned int final_offset)
{
	struct ext2_dir_entry *dirent;
	unsigned int rec_len;
#define DIRENT_MIN_LENGTH 12

	while ((offset < final_offset) &&
	       (offset <= fs->blocksize - DIRENT_MIN_LENGTH)) {
		dirent = (struct ext2_dir_entry *)(buf + offset);
		if (ext2fs_get_rec_len(fs, dirent, &rec_len))
			return 0;
		offset += rec_len;
		if ((rec_len < 8) ||
		    ((rec_len % 4) != 0) ||
		    ((ext2fs_dirent_name_len(dirent)+8) > (int) rec_len))
			return 0;
	}
	return (offset == final_offset);
}