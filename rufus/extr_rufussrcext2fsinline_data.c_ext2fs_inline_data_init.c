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
struct ext2_inline_data {char* ea_data; scalar_t__ ea_size; int /*<<< orphan*/  ino; int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_inline_data_ea_set (struct ext2_inline_data*) ; 

errcode_t ext2fs_inline_data_init(ext2_filsys fs, ext2_ino_t ino)
{
	struct ext2_inline_data data;
	char empty[1] = { '\0' };

	data.fs = fs;
	data.ino = ino;
	data.ea_size = 0;
	data.ea_data = empty;
	return ext2fs_inline_data_ea_set(&data);
}