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
struct super_block {int dummy; } ;

/* Variables and functions */

void ext3_warning (struct super_block * sb, const char * function,
                   char * fmt, ...)
{
#if DX_DEBUG
    va_list args;

    va_start(args, fmt);
    printk("EXT3-fs warning (device %s): %s: ",
           sb->s_id, function);
    printk(fmt, args);
    printk("\n");
    va_end(args);
#endif
}