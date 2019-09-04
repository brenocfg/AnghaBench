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
typedef  scalar_t__ io_channel ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_3__ {int flags; scalar_t__ image_io; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_NOT_IMAGE_FILE ; 
 int EXT2_FLAG_IMAGE_FILE ; 

errcode_t ext2fs_get_data_io(ext2_filsys fs, io_channel *old_io)
{
	if ((fs->flags & EXT2_FLAG_IMAGE_FILE) == 0)
		return EXT2_ET_NOT_IMAGE_FILE;
	if (old_io) {
		*old_io = (fs->image_io == fs->io) ? 0 : fs->io;
	}
	return 0;
}