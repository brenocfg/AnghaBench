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
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_bitmaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

errcode_t ext2fs_write_block_bitmap (ext2_filsys fs)
{
	return write_bitmaps(fs, 0, 1);
}