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
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__* PSINGLE_LIST_ENTRY ;

/* Variables and functions */

PSINGLE_LIST_ENTRY FlushList(PSINGLE_LIST_ENTRY ListHead)
{
    PSINGLE_LIST_ENTRY Ret = ListHead->Next;
    ListHead->Next = NULL;
    return Ret;
}