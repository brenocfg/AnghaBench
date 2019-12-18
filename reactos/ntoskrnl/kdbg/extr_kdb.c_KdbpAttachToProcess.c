#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_13__ {int /*<<< orphan*/  ThreadListHead; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Flink; } ;
struct TYPE_12__ {TYPE_1__ ThreadListHead; } ;
struct TYPE_10__ {int /*<<< orphan*/  UniqueThread; } ;
struct TYPE_11__ {TYPE_2__ Cid; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/ * PLIST_ENTRY ;
typedef  TYPE_3__* PETHREAD ;
typedef  TYPE_4__* PEPROCESS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_3__* CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHREAD ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_7__* KdbCurrentProcess ; 
 int /*<<< orphan*/  KdbpAttachToThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KdbpPrint (char*,scalar_t__) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_4__*) ; 
 int /*<<< orphan*/  PsLookupProcessByProcessId (scalar_t__,TYPE_4__**) ; 
 int /*<<< orphan*/  ThreadListEntry ; 

BOOLEAN
KdbpAttachToProcess(
    PVOID ProcessId)
{
    PEPROCESS Process = NULL;
    PETHREAD Thread;
    PLIST_ENTRY Entry;

    /* Get a pointer to the process */
    if (!NT_SUCCESS(PsLookupProcessByProcessId(ProcessId, &Process)))
    {
        KdbpPrint("Invalid process id: 0x%08x\n", (ULONG_PTR)ProcessId);
        return FALSE;
    }

    Entry = Process->ThreadListHead.Flink;
    ObDereferenceObject(Process);
    if (Entry == &KdbCurrentProcess->ThreadListHead)
    {
        KdbpPrint("No threads in process 0x%p, cannot attach to process!\n", ProcessId);
        return FALSE;
    }

    Thread = CONTAINING_RECORD(Entry, ETHREAD, ThreadListEntry);

    return KdbpAttachToThread(Thread->Cid.UniqueThread);
}