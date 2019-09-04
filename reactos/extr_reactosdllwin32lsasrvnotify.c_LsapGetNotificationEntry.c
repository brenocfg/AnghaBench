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
struct TYPE_8__ {struct TYPE_8__* Flink; } ;
struct TYPE_7__ {scalar_t__ EventHandle; scalar_t__ InformationClass; } ;
typedef  scalar_t__ POLICY_NOTIFICATION_INFORMATION_CLASS ;
typedef  TYPE_1__* PLSA_NOTIFICATION_ENTRY ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  LSA_NOTIFICATION_ENTRY ; 
 TYPE_2__ NotificationListHead ; 

__attribute__((used)) static
PLSA_NOTIFICATION_ENTRY
LsapGetNotificationEntry(
    HANDLE EventHandle,
    POLICY_NOTIFICATION_INFORMATION_CLASS InformationClass)
{
    PLIST_ENTRY NotificationEntry;
    PLSA_NOTIFICATION_ENTRY CurrentNotification;

    NotificationEntry = NotificationListHead.Flink;
    while (NotificationEntry != &NotificationListHead)
    {
        CurrentNotification = CONTAINING_RECORD(NotificationEntry, LSA_NOTIFICATION_ENTRY, Entry);

        if ((CurrentNotification->EventHandle == EventHandle) &&
            (CurrentNotification->InformationClass == InformationClass))
            return CurrentNotification;

        NotificationEntry = NotificationEntry->Flink;
    }

    return NULL;
}