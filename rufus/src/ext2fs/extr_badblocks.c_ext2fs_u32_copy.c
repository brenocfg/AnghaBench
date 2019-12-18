#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2_u32_list ;
typedef  scalar_t__ errcode_t ;
struct TYPE_5__ {int /*<<< orphan*/  badblocks_flags; int /*<<< orphan*/  list; int /*<<< orphan*/  num; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ make_u32_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 

errcode_t ext2fs_u32_copy(ext2_u32_list src, ext2_u32_list *dest)
{
	errcode_t	retval;

	retval = make_u32_list(src->size, src->num, src->list, dest);
	if (retval)
		return retval;
	(*dest)->badblocks_flags = src->badblocks_flags;
	return 0;
}