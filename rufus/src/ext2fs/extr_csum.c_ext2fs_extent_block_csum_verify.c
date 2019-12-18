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
struct ext3_extent_tail {int /*<<< orphan*/  et_checksum; } ;
struct ext3_extent_header {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ ext2fs_extent_block_csum (TYPE_1__*,int /*<<< orphan*/ ,struct ext3_extent_header*,scalar_t__*) ; 
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ext3_extent_tail* get_extent_tail (struct ext3_extent_header*) ; 

int ext2fs_extent_block_csum_verify(ext2_filsys fs, ext2_ino_t inum,
				    struct ext3_extent_header *eh)
{
	errcode_t retval;
	__u32 provided, calculated;
	struct ext3_extent_tail *t = get_extent_tail(eh);

	/*
	 * The extent tree structures are accessed in LE order, so we must
	 * swap the checksum bytes here.
	 */
	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 1;

	provided = ext2fs_le32_to_cpu(t->et_checksum);
	retval = ext2fs_extent_block_csum(fs, inum, eh, &calculated);
	if (retval)
		return 0;

	return provided == calculated;
}