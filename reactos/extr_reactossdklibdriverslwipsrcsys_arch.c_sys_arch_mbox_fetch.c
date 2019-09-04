#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32_t ;
struct TYPE_9__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Event; int /*<<< orphan*/  ListHead; } ;
typedef  TYPE_1__ sys_mbox_t ;
typedef  int UINT64 ;
struct TYPE_11__ {int QuadPart; } ;
struct TYPE_10__ {int /*<<< orphan*/ * Message; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PLWIP_MESSAGE_CONTAINER ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_2__*) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int Int32x32To64 (scalar_t__,int) ; 
 scalar_t__ IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_3__*) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ KeWaitForMultipleObjects (int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  LWIP_MESSAGE_CONTAINER ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  PsTerminateSystemThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ STATUS_WAIT_0 ; 
 scalar_t__ STATUS_WAIT_1 ; 
 scalar_t__ SYS_ARCH_TIMEOUT ; 
 int /*<<< orphan*/  TerminationEvent ; 
 int /*<<< orphan*/  WaitAny ; 

u32_t
sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    LARGE_INTEGER LargeTimeout, PreWaitTime, PostWaitTime;
    UINT64 TimeDiff;
    NTSTATUS Status;
    PVOID Message;
    PLWIP_MESSAGE_CONTAINER Container;
    PLIST_ENTRY Entry;
    KIRQL OldIrql;
    PVOID WaitObjects[] = {&mbox->Event, &TerminationEvent};
    
    LargeTimeout.QuadPart = Int32x32To64(timeout, -10000);
    
    KeQuerySystemTime(&PreWaitTime);

    Status = KeWaitForMultipleObjects(2,
                                      WaitObjects,
                                      WaitAny,
                                      Executive,
                                      KernelMode,
                                      FALSE,
                                      timeout != 0 ? &LargeTimeout : NULL,
                                      NULL);

    if (Status == STATUS_WAIT_0)
    {
        KeAcquireSpinLock(&mbox->Lock, &OldIrql);
        Entry = RemoveHeadList(&mbox->ListHead);
        ASSERT(Entry);
        if (IsListEmpty(&mbox->ListHead))
            KeClearEvent(&mbox->Event);
        KeReleaseSpinLock(&mbox->Lock, OldIrql);
        
        Container = CONTAINING_RECORD(Entry, LWIP_MESSAGE_CONTAINER, ListEntry);
        Message = Container->Message;
        ExFreePool(Container);
        
        if (msg)
            *msg = Message;

        KeQuerySystemTime(&PostWaitTime);
        TimeDiff = PostWaitTime.QuadPart - PreWaitTime.QuadPart;
        TimeDiff /= 10000;
        
        return TimeDiff;
    }
    else if (Status == STATUS_WAIT_1)
    {
        /* DON'T remove ourselves from the thread list! */
        PsTerminateSystemThread(STATUS_SUCCESS);
        
        /* We should never get here! */
        ASSERT(FALSE);
        
        return 0;
    }
    
    return SYS_ARCH_TIMEOUT;
}