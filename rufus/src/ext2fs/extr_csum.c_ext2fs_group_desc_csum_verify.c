#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;

/* Variables and functions */
 scalar_t__ ext2fs_bg_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_group_desc_csum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_has_group_desc_csum (int /*<<< orphan*/ ) ; 

int ext2fs_group_desc_csum_verify(ext2_filsys fs, dgrp_t group)
{
	if (ext2fs_has_group_desc_csum(fs) &&
	    (ext2fs_bg_checksum(fs, group) !=
	     ext2fs_group_desc_csum(fs, group)))
		return 0;

	return 1;
}