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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {struct TYPE_7__* Flink; } ;
struct TYPE_6__ {scalar_t__ InformationClass; scalar_t__ EventHandle; } ;
typedef  scalar_t__ POLICY_NOTIFICATION_INFORMATION_CLASS ;
typedef  TYPE_1__* PLSA_NOTIFICATION_ENTRY ;
typedef  TYPE_2__* PLIST_ENTRY ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  LSA_NOTIFICATION_ENTRY ; 
 TYPE_2__ NotificationListHead ; 
 int /*<<< orphan*/  NotificationListLock ; 
 int /*<<< orphan*/  RtlAcquireResourceShared (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlReleaseResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

VOID
LsapNotifyPolicyChange(
    POLICY_NOTIFICATION_INFORMATION_CLASS InformationClass)
{
    PLIST_ENTRY NotificationEntry;
    PLSA_NOTIFICATION_ENTRY CurrentNotification;

    FIXME("LsapNotifyPolicyChange(%lu)\n", InformationClass);

    /* Acquire the notification list lock shared */
    RtlAcquireResourceShared(&NotificationListLock, TRUE);

    NotificationEntry = NotificationListHead.Flink;
    while (NotificationEntry != &NotificationListHead)
    {
        CurrentNotification = CONTAINING_RECORD(NotificationEntry, LSA_NOTIFICATION_ENTRY, Entry);

        if (CurrentNotification->InformationClass == InformationClass)
        {
            FIXME("Notify event %p\n", CurrentNotification->EventHandle);

        }

        NotificationEntry = NotificationEntry->Flink;
    }

    /* Release the notification list lock */
    RtlReleaseResource(&NotificationListLock);
}