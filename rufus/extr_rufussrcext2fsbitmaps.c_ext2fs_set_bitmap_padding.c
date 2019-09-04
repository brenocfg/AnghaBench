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
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_set_generic_bmap_padding (int /*<<< orphan*/ ) ; 

void ext2fs_set_bitmap_padding(ext2fs_generic_bitmap map)
{
	ext2fs_set_generic_bmap_padding(map);
}