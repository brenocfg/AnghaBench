#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_6__ {struct TYPE_6__* Flink; } ;
struct TYPE_7__ {TYPE_1__ PageList; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/ * PEMS_PAGE ;
typedef  TYPE_2__* PEMS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EMS_PAGE ; 

__attribute__((used)) static PEMS_PAGE GetLogicalPage(PEMS_HANDLE HandleEntry, USHORT LogicalPage)
{
    PLIST_ENTRY Entry = HandleEntry->PageList.Flink;

    while (LogicalPage)
    {
        if (Entry == &HandleEntry->PageList) return NULL;
        LogicalPage--;
        Entry = Entry->Flink;
    }

    return (PEMS_PAGE)CONTAINING_RECORD(Entry, EMS_PAGE, Entry);
}