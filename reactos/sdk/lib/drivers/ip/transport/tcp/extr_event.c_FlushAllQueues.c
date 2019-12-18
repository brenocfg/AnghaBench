#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushConnectQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushListenQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushReceiveQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushSendQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushShutdownQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_FILE_CLOSED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

VOID
FlushAllQueues(PCONNECTION_ENDPOINT Connection, NTSTATUS Status)
{    
    ReferenceObject(Connection);
    
    // flush receive queue
    FlushReceiveQueue(Connection, Status, TRUE);

    /* We completed the reads successfully but we need to return failure now */
    if (Status == STATUS_SUCCESS)
    {
        Status = STATUS_FILE_CLOSED;
    }
    
    // flush listen queue
    FlushListenQueue(Connection, Status);
    
    // flush send queue
    FlushSendQueue(Connection, Status, TRUE);
    
    // flush connect queue
    FlushConnectQueue(Connection, Status);

    // flush shutdown queue
    FlushShutdownQueue(Connection, Status, TRUE);
    
    DereferenceObject(Connection);
}