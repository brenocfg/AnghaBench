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
struct ext4_xattr_item {size_t data_size; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static int ext4_xattr_item_alloc_data(struct ext4_xattr_item *item,
				      const void *orig_data, size_t data_size)
{
	void *data = NULL;
	ASSERT(!item->data);
	data = kmalloc(data_size, GFP_NOFS);
	if (!data)
		return -ENOMEM;

	if (orig_data)
		memcpy(data, orig_data, data_size);

	item->data = data;
	item->data_size = data_size;
	return 0;
}