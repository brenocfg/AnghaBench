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
typedef  TYPE_1__* ext2_filsys ;
struct TYPE_3__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 unsigned int EXT4_HTREE_LEVEL ; 
 unsigned int EXT4_HTREE_LEVEL_COMPAT ; 
 scalar_t__ ext2fs_has_feature_largedir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ext2_dir_htree_level(ext2_filsys fs)
{
	if (ext2fs_has_feature_largedir(fs->super))
		return EXT4_HTREE_LEVEL;

	return EXT4_HTREE_LEVEL_COMPAT;
}