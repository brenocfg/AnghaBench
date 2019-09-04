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
typedef  int /*<<< orphan*/  ext2_u32_list ;
typedef  scalar_t__ ext2_badblocks_list ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_u32_list_free (int /*<<< orphan*/ ) ; 

void ext2fs_badblocks_list_free(ext2_badblocks_list bb)
{
	ext2fs_u32_list_free((ext2_u32_list) bb);
}