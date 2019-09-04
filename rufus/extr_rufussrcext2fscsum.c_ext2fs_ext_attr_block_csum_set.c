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
struct ext2_ext_attr_header {int /*<<< orphan*/  h_checksum; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_ext_attr_block_csum (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_ext_attr_header*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_ext_attr_block_csum_set(ext2_filsys fs, ext2_ino_t inum,
					 blk64_t block,
					 struct ext2_ext_attr_header *hdr)
{
	errcode_t retval;
	__u32 crc;

	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 0;

	retval = ext2fs_ext_attr_block_csum(fs, inum, block, hdr, &crc);
	if (retval)
		return retval;
	hdr->h_checksum = ext2fs_cpu_to_le32(crc);
	return 0;
}