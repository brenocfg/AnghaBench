#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* Process; } ;
struct TYPE_3__ {int /*<<< orphan*/  ProcessHandle; } ;
typedef  int /*<<< orphan*/ * PHANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 TYPE_2__* CsrGetClientThread () ; 
 int DUPLICATE_SAME_ACCESS ; 
 int DUPLICATE_SAME_ATTRIBUTES ; 
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtDuplicateObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

NTSTATUS BaseSrvCreatePairWaitHandles(PHANDLE ServerEvent, PHANDLE ClientEvent)
{
    NTSTATUS Status;

    /* Create the event */
    Status = NtCreateEvent(ServerEvent, EVENT_ALL_ACCESS, NULL, NotificationEvent, FALSE);
    if (!NT_SUCCESS(Status)) return Status;

    /* Duplicate the event into the client process */
    Status = NtDuplicateObject(NtCurrentProcess(),
                               *ServerEvent,
                               CsrGetClientThread()->Process->ProcessHandle,
                               ClientEvent,
                               0,
                               0,
                               DUPLICATE_SAME_ATTRIBUTES | DUPLICATE_SAME_ACCESS);

    if (!NT_SUCCESS(Status)) NtClose(*ServerEvent);
    return Status;
}