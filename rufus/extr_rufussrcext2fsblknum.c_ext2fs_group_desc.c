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
struct opaque_ext2_group_desc {int dummy; } ;
struct ext2_group_desc {int dummy; } ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int dgrp_t ;
struct TYPE_3__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int EXT2_DESC_SIZE (int /*<<< orphan*/ ) ; 

struct ext2_group_desc *ext2fs_group_desc(ext2_filsys fs,
					  struct opaque_ext2_group_desc *gdp,
					  dgrp_t group)
{
	int desc_size = EXT2_DESC_SIZE(fs->super) & ~7;

	return (struct ext2_group_desc *)((char *)gdp + group * desc_size);
}