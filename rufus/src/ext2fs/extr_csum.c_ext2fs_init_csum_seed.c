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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_7__ {int /*<<< orphan*/  s_uuid; int /*<<< orphan*/  s_checksum_seed; } ;
struct TYPE_6__ {TYPE_3__* super; int /*<<< orphan*/  csum_seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_crc32c_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext2fs_has_feature_csum_seed (TYPE_3__*) ; 
 scalar_t__ ext2fs_has_feature_ea_inode (TYPE_3__*) ; 
 scalar_t__ ext2fs_has_feature_metadata_csum (TYPE_3__*) ; 

void ext2fs_init_csum_seed(ext2_filsys fs)
{
	if (ext2fs_has_feature_csum_seed(fs->super))
		fs->csum_seed = fs->super->s_checksum_seed;
	else if (ext2fs_has_feature_metadata_csum(fs->super) ||
		 ext2fs_has_feature_ea_inode(fs->super))
		fs->csum_seed = ext2fs_crc32c_le(~0, fs->super->s_uuid,
						 sizeof(fs->super->s_uuid));
}