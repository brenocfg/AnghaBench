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
typedef  int /*<<< orphan*/  ext2_extent_handle_t ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int /*<<< orphan*/  blk64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_extent_goto2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_extent_goto(ext2_extent_handle_t handle,
			     blk64_t blk)
{
	return ext2fs_extent_goto2(handle, 0, blk);
}