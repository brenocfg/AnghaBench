#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_24__ {TYPE_3__* SocketContext; int /*<<< orphan*/  Lock; int /*<<< orphan*/  ListenRequest; } ;
struct TYPE_23__ {int /*<<< orphan*/  Parameters; } ;
struct TYPE_22__ {scalar_t__ state; } ;
struct TYPE_20__ {int /*<<< orphan*/  RequestContext; } ;
struct TYPE_21__ {TYPE_5__* AssociatedEndpoint; scalar_t__ Information; int /*<<< orphan*/  Status; TYPE_1__ Request; } ;
typedef  int /*<<< orphan*/  PTDI_REQUEST_KERNEL ;
typedef  TYPE_2__* PTDI_BUCKET ;
typedef  TYPE_3__* PTCP_PCB ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_4__* PIO_STACK_LOCATION ;
typedef  TYPE_5__* PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CLOSED ; 
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompleteBucket (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_TCP ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_5__*) ; 
 int /*<<< orphan*/  ExInterlockedRemoveHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_4__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibTCPAccept (TYPE_3__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  LibTCPClose (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockObject (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReferenceObject (TYPE_5__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TCPCheckPeerForAccept (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_BUCKET ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnlockObject (TYPE_5__*,int /*<<< orphan*/ ) ; 

VOID
TCPAcceptEventHandler(void *arg, PTCP_PCB newpcb)
{
    PCONNECTION_ENDPOINT Connection = (PCONNECTION_ENDPOINT)arg;
    PTDI_BUCKET Bucket;
    PLIST_ENTRY Entry;
    PIRP Irp;
    NTSTATUS Status;
    KIRQL OldIrql;
        
    ReferenceObject(Connection);
    
    while ((Entry = ExInterlockedRemoveHeadList(&Connection->ListenRequest, &Connection->Lock)))
    {
        PIO_STACK_LOCATION IrpSp;
        
        Bucket = CONTAINING_RECORD( Entry, TDI_BUCKET, Entry );
        
        Irp = Bucket->Request.RequestContext;
        IrpSp = IoGetCurrentIrpStackLocation( Irp );
        
        TI_DbgPrint(DEBUG_TCP,("[IP, TCPAcceptEventHandler] Getting the socket\n"));
        
        Status = TCPCheckPeerForAccept(newpcb,
                                       (PTDI_REQUEST_KERNEL)&IrpSp->Parameters);
        
        TI_DbgPrint(DEBUG_TCP,("Socket: Status: %x\n", Status));
        
        Bucket->Status = Status;
        Bucket->Information = 0;
                
        if (Status == STATUS_SUCCESS)
        {
            LockObject(Bucket->AssociatedEndpoint, &OldIrql);

            /* sanity assert...this should never be in anything else but a CLOSED state */
            ASSERT( ((PTCP_PCB)Bucket->AssociatedEndpoint->SocketContext)->state == CLOSED );
            
            /*  free socket context created in FileOpenConnection, as we're using a new one */
            LibTCPClose(Bucket->AssociatedEndpoint, TRUE, FALSE);

            /* free previously created socket context (we don't use it, we use newpcb) */
            Bucket->AssociatedEndpoint->SocketContext = newpcb;
            
            LibTCPAccept(newpcb, (PTCP_PCB)Connection->SocketContext, Bucket->AssociatedEndpoint);

            UnlockObject(Bucket->AssociatedEndpoint, OldIrql);
        }
        
        DereferenceObject(Bucket->AssociatedEndpoint);
        
        CompleteBucket(Connection, Bucket, FALSE);

        if (Status == STATUS_SUCCESS)
        {
            break;
        }
    }
    
    DereferenceObject(Connection);
}