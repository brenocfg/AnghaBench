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
struct TYPE_3__ {int blocksize; } ;

/* Variables and functions */
 unsigned int EXT4_MAX_REC_LEN ; 

errcode_t ext2fs_get_rec_len(ext2_filsys fs,
			     struct ext2_dir_entry *dirent,
			     unsigned int *rec_len)
{
	unsigned int len = dirent->rec_len;

	if (fs->blocksize < 65536)
		*rec_len = len;
	else if (len == EXT4_MAX_REC_LEN || len == 0)
		*rec_len = fs->blocksize;
	else 
		*rec_len = (len & 65532) | ((len & 3) << 16);
	return 0;
}