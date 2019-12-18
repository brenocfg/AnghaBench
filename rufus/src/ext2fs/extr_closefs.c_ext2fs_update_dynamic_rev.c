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
struct ext2_super_block {scalar_t__ s_rev_level; int /*<<< orphan*/  s_inode_size; int /*<<< orphan*/  s_first_ino; } ;
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_3__ {struct ext2_super_block* super; } ;

/* Variables and functions */
 scalar_t__ EXT2_DYNAMIC_REV ; 
 int /*<<< orphan*/  EXT2_GOOD_OLD_FIRST_INO ; 
 int /*<<< orphan*/  EXT2_GOOD_OLD_INODE_SIZE ; 
 scalar_t__ EXT2_GOOD_OLD_REV ; 

void ext2fs_update_dynamic_rev(ext2_filsys fs)
{
	struct ext2_super_block *sb = fs->super;

	if (sb->s_rev_level > EXT2_GOOD_OLD_REV)
		return;

	sb->s_rev_level = EXT2_DYNAMIC_REV;
	sb->s_first_ino = EXT2_GOOD_OLD_FIRST_INO;
	sb->s_inode_size = EXT2_GOOD_OLD_INODE_SIZE;
	/* s_uuid is handled by e2fsck already */
	/* other fields should be left alone */
}