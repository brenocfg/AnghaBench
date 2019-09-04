#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {struct TYPE_8__* Flink; } ;
struct TYPE_7__ {scalar_t__ SessionId; } ;
typedef  TYPE_1__* PVDM_CONSOLE_RECORD ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_2__ VDMConsoleListHead ; 
 int /*<<< orphan*/  VDM_CONSOLE_RECORD ; 

NTSTATUS GetConsoleRecordBySessionId(ULONG TaskId, PVDM_CONSOLE_RECORD *Record)
{
    PLIST_ENTRY i;
    PVDM_CONSOLE_RECORD CurrentRecord = NULL;

    /* Search for a record that has the same console handle */
    for (i = VDMConsoleListHead.Flink; i != &VDMConsoleListHead; i = i->Flink)
    {
        CurrentRecord = CONTAINING_RECORD(i, VDM_CONSOLE_RECORD, Entry);
        if (CurrentRecord->SessionId == TaskId) break;
    }

    /* Check if nothing was found */
    if (i == &VDMConsoleListHead) CurrentRecord = NULL;

    *Record = CurrentRecord;
    return CurrentRecord ? STATUS_SUCCESS : STATUS_NOT_FOUND;
}