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
typedef  TYPE_1__* ext2fs_generic_bitmap_32 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
struct TYPE_2__ {scalar_t__ base_error_code; scalar_t__ description; } ;

/* Variables and functions */
 int /*<<< orphan*/  com_err (int /*<<< orphan*/ ,scalar_t__,char*,unsigned long,...) ; 

void ext2fs_warn_bitmap2(ext2fs_generic_bitmap gen_bitmap,
			    int code, unsigned long arg)
{
	ext2fs_generic_bitmap_32 bitmap = (ext2fs_generic_bitmap_32) gen_bitmap;

#ifndef OMIT_COM_ERR
	if (bitmap->description)
		com_err(0, bitmap->base_error_code+code,
			"#%lu for %s", arg, bitmap->description);
	else
		com_err(0, bitmap->base_error_code + code, "#%lu", arg);
#endif
}