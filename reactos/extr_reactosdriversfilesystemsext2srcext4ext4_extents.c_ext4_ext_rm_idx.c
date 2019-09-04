#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_ext_path {TYPE_1__* p_hdr; int /*<<< orphan*/  p_idx; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ eh_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 int ext4_ext_dirty (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_free_blocks (void*,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_idx_pblock (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 

int ext4_ext_rm_idx(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path)
{
	int err;
	ext4_fsblk_t leaf;

	/* free index block */
	path--;
	leaf = ext4_idx_pblock(path->p_idx);
	BUG_ON(path->p_hdr->eh_entries == 0);
	if ((err = ext4_ext_get_access(icb, handle, inode, path)))
		return err;
	path->p_hdr->eh_entries = cpu_to_le16(le16_to_cpu(path->p_hdr->eh_entries)-1);
	if ((err = ext4_ext_dirty(icb, handle, inode, path)))
		return err;
	ext4_free_blocks(icb, handle, inode, NULL, leaf, 1, 0);
	return err;
}