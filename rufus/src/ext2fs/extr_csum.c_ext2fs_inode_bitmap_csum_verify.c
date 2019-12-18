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
struct ext4_group_desc {int bg_inode_bitmap_csum_lo; scalar_t__ bg_inode_bitmap_csum_hi; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; int /*<<< orphan*/  csum_seed; int /*<<< orphan*/  group_desc; } ;

/* Variables and functions */
 scalar_t__ EXT2_DESC_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_BG_INODE_BITMAP_CSUM_HI_END ; 
 int ext2fs_crc32c_le (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ ext2fs_group_desc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 

int ext2fs_inode_bitmap_csum_verify(ext2_filsys fs, dgrp_t group,
				    char *bitmap, int size)
{
	struct ext4_group_desc *gdp = (struct ext4_group_desc *)
			ext2fs_group_desc(fs, fs->group_desc, group);
	__u32 provided, calculated;

	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 1;
	provided = gdp->bg_inode_bitmap_csum_lo;
	calculated = ext2fs_crc32c_le(fs->csum_seed, (unsigned char *)bitmap,
				      size);
	if (EXT2_DESC_SIZE(fs->super) >= EXT4_BG_INODE_BITMAP_CSUM_HI_END)
		provided |= (__u32)gdp->bg_inode_bitmap_csum_hi << 16;
	else
		calculated &= 0xFFFF;

	return provided == calculated;
}