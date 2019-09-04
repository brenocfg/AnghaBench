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
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 

errcode_t ext2fs_mmp_clear(ext2_filsys fs)
{
#ifdef CONFIG_MMP
	errcode_t retval = 0;

	if (!(fs->flags & EXT2_FLAG_RW))
		return EXT2_ET_RO_FILSYS;

	retval = ext2fs_mmp_reset(fs);

	return retval;
#else
	return EXT2_ET_OP_NOT_SUPPORTED;
#endif
}