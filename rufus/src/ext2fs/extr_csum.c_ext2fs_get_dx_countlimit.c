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
struct ext2_dx_countlimit {int dummy; } ;
struct ext2_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_dx_countlimit (int /*<<< orphan*/ ,struct ext2_dir_entry*,struct ext2_dx_countlimit**,int*,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_get_dx_countlimit(ext2_filsys fs,
				   struct ext2_dir_entry *dirent,
				   struct ext2_dx_countlimit **cc,
				   int *offset)
{
	return __get_dx_countlimit(fs, dirent, cc, offset, 0);
}