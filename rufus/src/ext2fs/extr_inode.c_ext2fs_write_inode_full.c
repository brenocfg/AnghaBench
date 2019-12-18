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
struct ext2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_write_inode2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ext2_inode*,int,int /*<<< orphan*/ ) ; 

errcode_t ext2fs_write_inode_full(ext2_filsys fs, ext2_ino_t ino,
				  struct ext2_inode * inode, int bufsize)
{
	return ext2fs_write_inode2(fs, ino, inode, bufsize, 0);
}