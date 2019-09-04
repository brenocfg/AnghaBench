#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int l_i_file_acl_high; } ;
struct TYPE_6__ {TYPE_1__ linux2; } ;
struct ext2_inode {TYPE_2__ osd2; scalar_t__ i_file_acl; } ;
typedef  TYPE_3__* ext2_filsys ;
typedef  scalar_t__ blk64_t ;
typedef  int __u64 ;
struct TYPE_7__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ ext2fs_has_feature_64bit (int /*<<< orphan*/ ) ; 

void ext2fs_file_acl_block_set(ext2_filsys fs, struct ext2_inode *inode,
			       blk64_t blk)
{
	inode->i_file_acl = blk;
	if (fs && ext2fs_has_feature_64bit(fs->super))
		inode->osd2.linux2.l_i_file_acl_high = (__u64) blk >> 32;
}