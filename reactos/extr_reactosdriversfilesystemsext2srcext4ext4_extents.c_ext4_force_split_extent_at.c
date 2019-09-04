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
struct ext4_ext_path {size_t p_depth; int /*<<< orphan*/  p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int EXT4_EXT_MARK_UNWRIT1 ; 
 int EXT4_EXT_MARK_UNWRIT2 ; 
 int EXT4_EX_NOCACHE ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int EXT4_GET_BLOCKS_PRE_IO ; 
 int ext4_ext_is_unwritten (int /*<<< orphan*/ ) ; 
 int ext4_split_extent_at (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path**,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int
ext4_force_split_extent_at(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path **ppath, ext4_lblk_t lblk,
		int nofail)
{
	struct ext4_ext_path *path = *ppath;
	int unwritten = ext4_ext_is_unwritten(path[path->p_depth].p_ext);

	return ext4_split_extent_at(icb, handle, inode, ppath, lblk, unwritten ?
			EXT4_EXT_MARK_UNWRIT1|EXT4_EXT_MARK_UNWRIT2 : 0,
			EXT4_EX_NOCACHE | EXT4_GET_BLOCKS_PRE_IO |
			(nofail ? EXT4_GET_BLOCKS_METADATA_NOFAIL:0));
}