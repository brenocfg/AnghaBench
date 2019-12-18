#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ext2_dir_entry {unsigned int rec_len; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_3__ {unsigned int blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned int EXT4_MAX_REC_LEN ; 

errcode_t ext2fs_set_rec_len(ext2_filsys fs,
			     unsigned int len,
			     struct ext2_dir_entry *dirent)
{
	if ((len > fs->blocksize) || (fs->blocksize > (1 << 18)) || (len & 3))
		return EINVAL;
	if (len < 65536) {
		dirent->rec_len = len;
		return 0;
	}
	if (len == fs->blocksize) {
		if (fs->blocksize == 65536)
			dirent->rec_len = EXT4_MAX_REC_LEN;
		else 
			dirent->rec_len = 0;
	} else
		dirent->rec_len = (len & 65532) | ((len >> 16) & 3);
	return 0;
}