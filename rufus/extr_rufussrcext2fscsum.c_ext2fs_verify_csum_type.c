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
struct ext2_super_block {scalar_t__ s_checksum_type; } ;
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_3__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ EXT2_CRC32C_CHKSUM ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 

int ext2fs_verify_csum_type(ext2_filsys fs, struct ext2_super_block *sb)
{
	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 1;

	return sb->s_checksum_type == EXT2_CRC32C_CHKSUM;
}