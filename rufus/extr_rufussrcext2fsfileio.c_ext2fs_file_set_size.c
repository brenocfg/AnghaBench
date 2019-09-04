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
typedef  int /*<<< orphan*/  ext2_off_t ;
typedef  int /*<<< orphan*/  ext2_file_t ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_file_set_size2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_file_set_size(ext2_file_t file, ext2_off_t size)
{
	return ext2fs_file_set_size2(file, size);
}