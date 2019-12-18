#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {int /*<<< orphan*/  SendRequest; int /*<<< orphan*/  Lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  Status; scalar_t__ Information; int /*<<< orphan*/  Request; } ;
typedef  TYPE_1__* PTDI_BUCKET ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_2__* PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompleteBucket (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_TCP ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_2__*) ; 
 int /*<<< orphan*/  ExInterlockedRemoveHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReferenceObject (TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TDI_BUCKET ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID
FlushSendQueue(PCONNECTION_ENDPOINT Connection, const NTSTATUS Status, const BOOLEAN interlocked)
{
    PTDI_BUCKET Bucket;
    PLIST_ENTRY Entry;
    
    ReferenceObject(Connection);

    if (interlocked)
    {
        while ((Entry = ExInterlockedRemoveHeadList(&Connection->SendRequest, &Connection->Lock)))
        {
            Bucket = CONTAINING_RECORD( Entry, TDI_BUCKET, Entry );    
        
            TI_DbgPrint(DEBUG_TCP,
                        ("Completing Send request: %x %x\n",
                         Bucket->Request, Status));
        
            Bucket->Status = Status;
            Bucket->Information = 0;
        
            CompleteBucket(Connection, Bucket, FALSE);
        }
    }
    else
    {
        while (!IsListEmpty(&Connection->SendRequest))
        {
            Entry = RemoveHeadList(&Connection->SendRequest);
            
            Bucket = CONTAINING_RECORD(Entry, TDI_BUCKET, Entry);
            
            Bucket->Information = 0;
            Bucket->Status = Status;
            
            CompleteBucket(Connection, Bucket, FALSE);
        }
    }

    DereferenceObject(Connection);
}