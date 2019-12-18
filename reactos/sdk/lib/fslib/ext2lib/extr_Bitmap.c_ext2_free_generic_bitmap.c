#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* bitmap; } ;
typedef  TYPE_1__* PEXT2_GENERIC_BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 

void ext2_free_generic_bitmap(PEXT2_GENERIC_BITMAP bitmap)
{
    if (!bitmap)
        return;

    if (bitmap->bitmap)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, bitmap->bitmap);
        bitmap->bitmap = 0;
    }

    RtlFreeHeap(RtlGetProcessHeap(), 0, bitmap);
}