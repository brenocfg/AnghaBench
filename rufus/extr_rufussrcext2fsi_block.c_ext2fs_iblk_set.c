#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int l_i_blocks_hi; } ;
struct TYPE_7__ {TYPE_1__ linux2; } ;
struct ext2_inode {int i_flags; int i_blocks; TYPE_2__ osd2; } ;
typedef  TYPE_3__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int blk64_t ;
struct TYPE_8__ {int blocksize; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int EXT2FS_CLUSTER_RATIO (TYPE_3__*) ; 
 int EXT4_HUGE_FILE_FL ; 
 scalar_t__ ext2fs_has_feature_huge_file (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_iblk_set(ext2_filsys fs, struct ext2_inode *inode, blk64_t b)
{
	if (!ext2fs_has_feature_huge_file(fs->super) ||
	    !(inode->i_flags & EXT4_HUGE_FILE_FL))
		b *= fs->blocksize / 512;
	b *= EXT2FS_CLUSTER_RATIO(fs);

	inode->i_blocks = b & 0xFFFFFFFF;
	if (ext2fs_has_feature_huge_file(fs->super))
		inode->osd2.linux2.l_i_blocks_hi = b >> 32;
	else if (b >> 32)
		return EOVERFLOW;
	return 0;
}