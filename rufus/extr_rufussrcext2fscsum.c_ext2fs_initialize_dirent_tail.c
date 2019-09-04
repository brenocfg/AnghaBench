#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ext2_dir_entry_tail {int /*<<< orphan*/  det_reserved_name_len; } ;
struct ext2_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_DIR_NAME_LEN_CSUM ; 
 int /*<<< orphan*/  ext2fs_set_rec_len (int /*<<< orphan*/ ,int,struct ext2_dir_entry*) ; 
 int /*<<< orphan*/  memset (struct ext2_dir_entry_tail*,int /*<<< orphan*/ ,int) ; 

void ext2fs_initialize_dirent_tail(ext2_filsys fs,
				   struct ext2_dir_entry_tail *t)
{
	memset(t, 0, sizeof(struct ext2_dir_entry_tail));
	ext2fs_set_rec_len(fs, sizeof(struct ext2_dir_entry_tail),
			   (struct ext2_dir_entry *)t);
	t->det_reserved_name_len = EXT2_DIR_NAME_LEN_CSUM;
}