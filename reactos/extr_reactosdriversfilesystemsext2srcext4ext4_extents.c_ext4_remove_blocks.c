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
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 unsigned long ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_free_blocks (void*,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_remove_blocks(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_extent *ex,
		unsigned long from, unsigned long to)
{
	struct buffer_head *bh;
	int i;

	if (from >= le32_to_cpu(ex->ee_block)
			&& to == le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex) - 1) {
		/* tail removal */
		unsigned long num, start;
		num = le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex) - from;
		start = ext4_ext_pblock(ex) + ext4_ext_get_actual_len(ex) - num;
		ext4_free_blocks(icb, handle, inode, NULL, start, num, 0);
	} else if (from == le32_to_cpu(ex->ee_block)
			&& to <= le32_to_cpu(ex->ee_block) + ext4_ext_get_actual_len(ex) - 1) {
	} else {
	}
	return 0;
}