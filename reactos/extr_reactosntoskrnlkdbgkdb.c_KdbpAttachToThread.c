#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_13__ {int /*<<< orphan*/  Pcb; } ;
struct TYPE_11__ {int /*<<< orphan*/  KernelStack; } ;
struct TYPE_12__ {TYPE_1__ Tcb; TYPE_3__* ThreadsProcess; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_2__* PETHREAD ;
typedef  TYPE_3__* PEPROCESS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdbApcState ; 
 TYPE_3__* KdbCurrentProcess ; 
 TYPE_2__* KdbCurrentThread ; 
 int /*<<< orphan*/ * KdbCurrentTrapFrame ; 
 TYPE_3__* KdbOriginalProcess ; 
 TYPE_2__* KdbOriginalThread ; 
 int /*<<< orphan*/  KdbThreadTrapFrame ; 
 int /*<<< orphan*/  KdbTrapFrame ; 
 int /*<<< orphan*/  KdbpKdbTrapFrameFromKernelStack (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 scalar_t__ KeIsExecutingDpc () ; 
 int /*<<< orphan*/  KeStackAttachProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeUnstackDetachProcess (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_2__*) ; 
 TYPE_3__* PsGetCurrentProcess () ; 
 int /*<<< orphan*/  PsLookupThreadByThreadId (scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
KdbpAttachToThread(
    PVOID ThreadId)
{
    PETHREAD Thread = NULL;
    PEPROCESS Process;

    /* Get a pointer to the thread */
    if (!NT_SUCCESS(PsLookupThreadByThreadId(ThreadId, &Thread)))
    {
        KdbpPrint("Invalid thread id: 0x%08x\n", (ULONG_PTR)ThreadId);
        return FALSE;
    }
    Process = Thread->ThreadsProcess;

    if (KeIsExecutingDpc() && Process != KdbCurrentProcess)
    {
        KdbpPrint("Cannot attach to thread within another process while executing a DPC.\n");
        ObDereferenceObject(Thread);
        return FALSE;
    }

    /* Save the current thread's context (if we previously attached to a thread) */
    if (KdbCurrentThread != KdbOriginalThread)
    {
        ASSERT(KdbCurrentTrapFrame == &KdbThreadTrapFrame);
        /* Actually, we can't save the context, there's no guarantee that there was a trap frame */
    }
    else
    {
        ASSERT(KdbCurrentTrapFrame == &KdbTrapFrame);
    }

    /* Switch to the thread's context */
    if (Thread != KdbOriginalThread)
    {
        /* The thread we're attaching to isn't the thread on which we entered
         * kdb and so the thread we're attaching to is not running. There
         * is no guarantee that it actually has a trap frame. So we have to
         * peek directly at the registers which were saved on the stack when the
         * thread was preempted in the scheduler */
        KdbpKdbTrapFrameFromKernelStack(Thread->Tcb.KernelStack,
                                        &KdbThreadTrapFrame);
        KdbCurrentTrapFrame = &KdbThreadTrapFrame;
    }
    else /* Switching back to original thread */
    {
        KdbCurrentTrapFrame = &KdbTrapFrame;
    }
    KdbCurrentThread = Thread;

    /* Attach to the thread's process */
    ASSERT(KdbCurrentProcess == PsGetCurrentProcess());
    if (KdbCurrentProcess != Process)
    {
        if (KdbCurrentProcess != KdbOriginalProcess) /* detach from previously attached process */
        {
            KeUnstackDetachProcess(&KdbApcState);
        }

        if (KdbOriginalProcess != Process)
        {
            KeStackAttachProcess(&Process->Pcb, &KdbApcState);
        }

        KdbCurrentProcess = Process;
    }

    ObDereferenceObject(Thread);
    return TRUE;
}