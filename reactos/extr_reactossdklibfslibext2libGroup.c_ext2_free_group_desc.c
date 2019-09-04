#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * group_desc; } ;
typedef  TYPE_1__* PEXT2_FILESYS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 

void ext2_free_group_desc(PEXT2_FILESYS Ext2Sys)
{
    if (Ext2Sys->group_desc)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, Ext2Sys->group_desc);
        Ext2Sys->group_desc = NULL;
    }
}