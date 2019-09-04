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
struct mmp_struct {int /*<<< orphan*/  mmp_checksum; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_has_feature_metadata_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_mmp_csum (TYPE_1__*,struct mmp_struct*) ; 

int ext2fs_mmp_csum_verify(ext2_filsys fs, struct mmp_struct *mmp)
{
	__u32 calculated;

	if (!ext2fs_has_feature_metadata_csum(fs->super))
		return 1;

	calculated = ext2fs_mmp_csum(fs, mmp);

	return ext2fs_le32_to_cpu(mmp->mmp_checksum) == calculated;
}