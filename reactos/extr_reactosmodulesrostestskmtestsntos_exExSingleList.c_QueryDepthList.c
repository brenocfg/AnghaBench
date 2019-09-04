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
typedef  scalar_t__ USHORT ;
struct TYPE_3__ {struct TYPE_3__* Next; } ;
typedef  TYPE_1__* PSINGLE_LIST_ENTRY ;

/* Variables and functions */

USHORT QueryDepthList(PSINGLE_LIST_ENTRY ListHead)
{
    USHORT Depth = 0;
    while (ListHead->Next)
    {
        ++Depth;
        ListHead = ListHead->Next;
    }
    return Depth;
}