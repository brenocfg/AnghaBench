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
struct ext2_super_block {int /*<<< orphan*/  s_checksum; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int EXT2_FLAG_SWAP_BYTES ; 
 int /*<<< orphan*/  EXT2_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ EXT4_FEATURE_RO_COMPAT_METADATA_CSUM ; 
 scalar_t__ ext2fs_cpu_to_le32 (scalar_t__) ; 
 scalar_t__ ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_superblock_csum (TYPE_1__*,struct ext2_super_block*) ; 

int ext2fs_superblock_csum_verify(ext2_filsys fs, struct ext2_super_block *sb)
{
	__u32 flag, calculated;

	if (fs->flags & EXT2_FLAG_SWAP_BYTES)
		flag = EXT4_FEATURE_RO_COMPAT_METADATA_CSUM;
	else
		flag = ext2fs_cpu_to_le32(EXT4_FEATURE_RO_COMPAT_METADATA_CSUM);

	if (!EXT2_HAS_RO_COMPAT_FEATURE(fs->super, flag))
		return 1;

	calculated = ext2fs_superblock_csum(fs, sb);

	return ext2fs_le32_to_cpu(sb->s_checksum) == calculated;
}