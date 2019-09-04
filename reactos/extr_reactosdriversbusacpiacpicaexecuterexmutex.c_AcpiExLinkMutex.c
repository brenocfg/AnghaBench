#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* Prev; TYPE_3__* Next; } ;
struct TYPE_8__ {TYPE_1__ Mutex; } ;
struct TYPE_7__ {TYPE_3__* AcquiredMutexList; } ;
typedef  TYPE_2__ ACPI_THREAD_STATE ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */

__attribute__((used)) static void
AcpiExLinkMutex (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_OPERAND_OBJECT     *ListHead;


    ListHead = Thread->AcquiredMutexList;

    /* This object will be the first object in the list */

    ObjDesc->Mutex.Prev = NULL;
    ObjDesc->Mutex.Next = ListHead;

    /* Update old first object to point back to this object */

    if (ListHead)
    {
        ListHead->Mutex.Prev = ObjDesc;
    }

    /* Update list head */

    Thread->AcquiredMutexList = ObjDesc;
}