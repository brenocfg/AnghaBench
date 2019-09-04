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
struct opaque_ext2_group_desc {int dummy; } ;
struct ext4_group_desc {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  dgrp_t ;

/* Variables and functions */
 scalar_t__ ext2fs_group_desc (int /*<<< orphan*/ ,struct opaque_ext2_group_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ext4_group_desc *ext4fs_group_desc(ext2_filsys fs,
					  struct opaque_ext2_group_desc *gdp,
					  dgrp_t group)
{
	return (struct ext4_group_desc *)ext2fs_group_desc(fs, gdp, group);
}