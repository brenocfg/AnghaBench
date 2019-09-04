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
struct ext2_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;

/* Variables and functions */
 scalar_t__ __get_dirent_tail (int /*<<< orphan*/ ,struct ext2_dir_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ext2fs_dirent_has_tail(ext2_filsys fs, struct ext2_dir_entry *dirent)
{
	return __get_dirent_tail(fs, dirent, NULL, 0) == 0;
}