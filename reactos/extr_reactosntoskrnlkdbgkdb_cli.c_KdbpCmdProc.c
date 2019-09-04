#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_12__ {scalar_t__ UniqueThread; } ;
struct TYPE_16__ {TYPE_1__ Cid; } ;
struct TYPE_13__ {scalar_t__ State; } ;
struct TYPE_15__ {scalar_t__ ImageFileName; TYPE_2__ Pcb; int /*<<< orphan*/  UniqueProcessId; } ;
struct TYPE_14__ {struct TYPE_14__* Flink; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PLIST_ENTRY ;
typedef  TYPE_4__* PEPROCESS ;
typedef  scalar_t__ PCHAR ;
typedef  TYPE_3__ LIST_ENTRY ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveProcessLinks ; 
 TYPE_4__* CONTAINING_RECORD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPROCESS ; 
 scalar_t__ FALSE ; 
 TYPE_4__* KdbCurrentProcess ; 
 TYPE_8__* KdbCurrentThread ; 
 int /*<<< orphan*/  KdbpAttachToProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_4__*) ; 
 scalar_t__ ProcessInMemory ; 
 scalar_t__ ProcessOutOfMemory ; 
 int /*<<< orphan*/  PsLookupProcessByProcessId (int /*<<< orphan*/ ,TYPE_4__**) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _stricmp (scalar_t__,char*) ; 
 int strtoul (scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdProc(
    ULONG Argc,
    PCHAR Argv[])
{
    PLIST_ENTRY Entry;
    PEPROCESS Process;
    BOOLEAN ReferencedProcess = FALSE;
    PCHAR State, pend, str1, str2;
    ULONG ul;
    extern LIST_ENTRY PsActiveProcessHead;

    if (Argc >= 2 && _stricmp(Argv[1], "list") == 0)
    {
        Entry = PsActiveProcessHead.Flink;
        if (!Entry || Entry == &PsActiveProcessHead)
        {
            KdbpPrint("No processes in the system!\n");
            return TRUE;
        }

        KdbpPrint("  PID         State       Filename\n");
        do
        {
            Process = CONTAINING_RECORD(Entry, EPROCESS, ActiveProcessLinks);

            if (Process == KdbCurrentProcess)
            {
                str1 = "\x1b[1m*";
                str2 = "\x1b[0m";
            }
            else
            {
                str1 = " ";
                str2 = "";
            }

            State = ((Process->Pcb.State == ProcessInMemory) ? "In Memory" :
                    ((Process->Pcb.State == ProcessOutOfMemory) ? "Out of Memory" : "In Transition"));

            KdbpPrint(" %s0x%08x  %-10s  %s%s\n",
                      str1,
                      Process->UniqueProcessId,
                      State,
                      Process->ImageFileName,
                      str2);

            Entry = Entry->Flink;
        }
        while(Entry != &PsActiveProcessHead);
    }
    else if (Argc >= 2 && _stricmp(Argv[1], "attach") == 0)
    {
        if (Argc < 3)
        {
            KdbpPrint("process attach: process id argument required!\n");
            return TRUE;
        }

        ul = strtoul(Argv[2], &pend, 0);
        if (Argv[2] == pend)
        {
            KdbpPrint("process attach: '%s' is not a valid process id!\n", Argv[2]);
            return TRUE;
        }

        if (!KdbpAttachToProcess((PVOID)ul))
        {
            return TRUE;
        }

        KdbpPrint("Attached to process 0x%08x, thread 0x%08x.\n", (ULONG)ul,
                  (ULONG)KdbCurrentThread->Cid.UniqueThread);
    }
    else
    {
        Process = KdbCurrentProcess;

        if (Argc >= 2)
        {
            ul = strtoul(Argv[1], &pend, 0);
            if (Argv[1] == pend)
            {
                KdbpPrint("proc: '%s' is not a valid process id!\n", Argv[1]);
                return TRUE;
            }

            if (!NT_SUCCESS(PsLookupProcessByProcessId((PVOID)ul, &Process)))
            {
                KdbpPrint("proc: Invalid process id!\n");
                return TRUE;
            }

            /* Remember our reference */
            ReferencedProcess = TRUE;
        }

        State = ((Process->Pcb.State == ProcessInMemory) ? "In Memory" :
                ((Process->Pcb.State == ProcessOutOfMemory) ? "Out of Memory" : "In Transition"));
        KdbpPrint("%s"
                  "  PID:             0x%08x\n"
                  "  State:           %s (0x%x)\n"
                  "  Image Filename:  %s\n",
                  (Argc < 2) ? "Current process:\n" : "",
                  Process->UniqueProcessId,
                  State, Process->Pcb.State,
                  Process->ImageFileName);

        /* Release our reference, if any */
        if (ReferencedProcess)
            ObDereferenceObject(Process);
    }

    return TRUE;
}