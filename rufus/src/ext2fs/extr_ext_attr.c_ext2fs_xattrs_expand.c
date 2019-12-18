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
struct ext2_xattr_handle {unsigned int capacity; struct ext2_xattr* attrs; } ;
struct ext2_xattr {int dummy; } ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2_xattr**) ; 
 scalar_t__ ext2fs_get_arrayzero (unsigned int,int,struct ext2_xattr**) ; 
 int /*<<< orphan*/  memcpy (struct ext2_xattr*,struct ext2_xattr*,int) ; 

__attribute__((used)) static errcode_t ext2fs_xattrs_expand(struct ext2_xattr_handle *h,
				      unsigned int expandby)
{
	struct ext2_xattr *new_attrs;
	errcode_t err;

	err = ext2fs_get_arrayzero(h->capacity + expandby,
				   sizeof(struct ext2_xattr), &new_attrs);
	if (err)
		return err;

	memcpy(new_attrs, h->attrs, h->capacity * sizeof(struct ext2_xattr));
	ext2fs_free_mem(&h->attrs);
	h->capacity += expandby;
	h->attrs = new_attrs;

	return 0;
}