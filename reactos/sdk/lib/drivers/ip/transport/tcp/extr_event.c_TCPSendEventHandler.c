#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16_t ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {int /*<<< orphan*/  DisconnectTimer; int /*<<< orphan*/  SendRequest; int /*<<< orphan*/  Lock; int /*<<< orphan*/  SocketContext; } ;
struct TYPE_14__ {int /*<<< orphan*/  MdlAddress; } ;
struct TYPE_12__ {TYPE_3__* RequestContext; } ;
struct TYPE_13__ {scalar_t__ Status; int /*<<< orphan*/  Information; TYPE_1__ Request; int /*<<< orphan*/  Entry; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PTDI_BUCKET ;
typedef  int /*<<< orphan*/  PMDL ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_3__* PIRP ;
typedef  TYPE_4__* PCONNECTION_ENDPOINT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompleteBucket (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_TCP ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_4__*) ; 
 int /*<<< orphan*/  ExInterlockedInsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExInterlockedRemoveHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushShutdownQueue (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IsListEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ KeCancelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LibTCPSend (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReferenceObject (TYPE_4__*) ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TCPTranslateError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_BUCKET ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 

VOID
TCPSendEventHandler(void *arg, const u16_t space)
{
    PCONNECTION_ENDPOINT Connection = (PCONNECTION_ENDPOINT)arg;
    PTDI_BUCKET Bucket;
    PLIST_ENTRY Entry;
    PIRP Irp;
    NTSTATUS Status;
    PMDL Mdl;
    ULONG BytesSent;
    
    ReferenceObject(Connection);

    while ((Entry = ExInterlockedRemoveHeadList(&Connection->SendRequest, &Connection->Lock)))
    {
        UINT SendLen = 0;
        PVOID SendBuffer = 0;
        
        Bucket = CONTAINING_RECORD( Entry, TDI_BUCKET, Entry );
        
        Irp = Bucket->Request.RequestContext;
        Mdl = Irp->MdlAddress;
        
        TI_DbgPrint(DEBUG_TCP,
                    ("Getting the user buffer from %x\n", Mdl));
        
        NdisQueryBuffer( Mdl, &SendBuffer, &SendLen );
        
        TI_DbgPrint(DEBUG_TCP,
                    ("Writing %d bytes to %x\n", SendLen, SendBuffer));
        
        TI_DbgPrint(DEBUG_TCP, ("Connection: %x\n", Connection));
        TI_DbgPrint
        (DEBUG_TCP,
         ("Connection->SocketContext: %x\n",
          Connection->SocketContext));
        
        Status = TCPTranslateError(LibTCPSend(Connection,
                                              SendBuffer,
                                              SendLen, &BytesSent, TRUE));
        
        TI_DbgPrint(DEBUG_TCP,("TCP Bytes: %d\n", BytesSent));
        
        if( Status == STATUS_PENDING )
        {
            ExInterlockedInsertHeadList(&Connection->SendRequest,
                                        &Bucket->Entry,
                                        &Connection->Lock);
            break;
        }
        else
        {
            TI_DbgPrint(DEBUG_TCP,
                        ("Completing Send request: %x %x\n",
                         Bucket->Request, Status));
            
            Bucket->Status = Status;
            Bucket->Information = (Bucket->Status == STATUS_SUCCESS) ? BytesSent : 0;
                        
            CompleteBucket(Connection, Bucket, FALSE);
        }
    }

    //  If we completed all outstanding send requests then finish all pending shutdown requests,
    //  cancel the timer and dereference the connection
    if (IsListEmpty(&Connection->SendRequest))
    {
        FlushShutdownQueue(Connection, STATUS_SUCCESS, FALSE);

        if (KeCancelTimer(&Connection->DisconnectTimer))
        {
            DereferenceObject(Connection);
        }
    }
    
    DereferenceObject(Connection);
}