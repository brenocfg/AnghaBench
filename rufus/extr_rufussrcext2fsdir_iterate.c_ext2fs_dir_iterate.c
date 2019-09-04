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
struct xlate {int (* func ) (struct ext2_dir_entry*,int,int,char*,void*) ;void* real_private; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_dir_iterate2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,struct xlate*) ; 
 int /*<<< orphan*/  xlate_func ; 

errcode_t ext2fs_dir_iterate(ext2_filsys fs,
			     ext2_ino_t dir,
			     int flags,
			     char *block_buf,
			     int (*func)(struct ext2_dir_entry *dirent,
					 int	offset,
					 int	blocksize,
					 char	*buf,
					 void	*priv_data),
			     void *priv_data)
{
	struct xlate xl;

	xl.real_private = priv_data;
	xl.func = func;

	return ext2fs_dir_iterate2(fs, dir, flags, block_buf,
				   xlate_func, &xl);
}