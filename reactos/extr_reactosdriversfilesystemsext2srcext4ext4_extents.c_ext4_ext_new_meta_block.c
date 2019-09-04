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
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_ext_find_goal (struct inode*,struct ext4_ext_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_new_meta_blocks (void*,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_fsblk_t
ext4_ext_new_meta_block(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path,
		struct ext4_extent *ex, int *err, unsigned int flags)
{
	ext4_fsblk_t goal, newblock;

	goal = ext4_ext_find_goal(inode, path, le32_to_cpu(ex->ee_block));
	newblock = ext4_new_meta_blocks(icb, handle, inode, goal, flags,
			NULL, err);
	return newblock;
}