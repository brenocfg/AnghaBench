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
struct TYPE_5__ {scalar_t__ l_i_blocks_hi; } ;
struct TYPE_6__ {TYPE_1__ linux2; } ;
struct ext2_inode {int i_blocks; TYPE_2__ osd2; } ;
typedef  TYPE_3__* ext2_filsys ;
typedef  int blk64_t ;
typedef  int __u64 ;
struct TYPE_7__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ ext2fs_has_feature_huge_file (int /*<<< orphan*/ ) ; 

blk64_t ext2fs_inode_i_blocks(ext2_filsys fs,
					struct ext2_inode *inode)
{
	return (inode->i_blocks |
		(ext2fs_has_feature_huge_file(fs->super) ?
		 (__u64)inode->osd2.linux2.l_i_blocks_hi << 32 : 0));
}