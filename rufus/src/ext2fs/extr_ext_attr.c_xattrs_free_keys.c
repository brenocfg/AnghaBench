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
struct ext2_xattr_handle {int capacity; scalar_t__ ibody_count; scalar_t__ count; struct ext2_xattr* attrs; } ;
struct ext2_xattr {scalar_t__ value; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_free_mem (scalar_t__*) ; 

__attribute__((used)) static void xattrs_free_keys(struct ext2_xattr_handle *h)
{
	struct ext2_xattr *a = h->attrs;
	int i;

	for (i = 0; i < h->capacity; i++) {
		if (a[i].name)
			ext2fs_free_mem(&a[i].name);
		if (a[i].value)
			ext2fs_free_mem(&a[i].value);
	}
	h->count = 0;
	h->ibody_count = 0;
}