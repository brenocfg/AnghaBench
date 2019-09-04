#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Complete ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int Protocol; int /*<<< orphan*/  Port; int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Complete ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  Lock; int /*<<< orphan*/  ReceiveQueue; int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  Connection; } ;
typedef  TYPE_1__* PVOID ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_1__* PDATAGRAM_SEND_REQUEST ;
typedef  TYPE_3__* PDATAGRAM_RECEIVE_REQUEST ;
typedef  TYPE_1__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_FILE_TAG ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AddressFileListLock ; 
 void* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATAGRAM_RECEIVE_REQUEST ; 
 int /*<<< orphan*/  DATAGRAM_SEND_REQUEST ; 
 int /*<<< orphan*/  DATAGRAM_SEND_TAG ; 
 int /*<<< orphan*/  DEBUG_ADDRFILE ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExInterlockedRemoveHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  RemoveEntityByContext (TYPE_1__*) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_CANCELLED ; 
 int /*<<< orphan*/  TCPFreePort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDPFreePort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID AddrFileFree(
    PVOID Object)
/*
 * FUNCTION: Frees an address file object
 * ARGUMENTS:
 *     Object = Pointer to address file object to free
 */
{
  PADDRESS_FILE AddrFile = Object;
  KIRQL OldIrql;
  PDATAGRAM_RECEIVE_REQUEST ReceiveRequest;
  PDATAGRAM_SEND_REQUEST SendRequest;
  PLIST_ENTRY CurrentEntry;

  TI_DbgPrint(MID_TRACE, ("Called.\n"));

  /* We should not be associated with a connection here */
  ASSERT(!AddrFile->Connection);

  /* Remove address file from the global list */
  TcpipAcquireSpinLock(&AddressFileListLock, &OldIrql);
  RemoveEntryList(&AddrFile->ListEntry);
  TcpipReleaseSpinLock(&AddressFileListLock, OldIrql);

  /* FIXME: Kill TCP connections on this address file object */

  /* Return pending requests with error */

  TI_DbgPrint(DEBUG_ADDRFILE, ("Aborting receive requests on AddrFile at (0x%X).\n", AddrFile));

  /* Go through pending receive request list and cancel them all */
  while ((CurrentEntry = ExInterlockedRemoveHeadList(&AddrFile->ReceiveQueue, &AddrFile->Lock))) {
    ReceiveRequest = CONTAINING_RECORD(CurrentEntry, DATAGRAM_RECEIVE_REQUEST, ListEntry);
    (*ReceiveRequest->Complete)(ReceiveRequest->Context, STATUS_CANCELLED, 0);
    /* ExFreePoolWithTag(ReceiveRequest, DATAGRAM_RECV_TAG); FIXME: WTF? */
  }

  TI_DbgPrint(DEBUG_ADDRFILE, ("Aborting send requests on address file at (0x%X).\n", AddrFile));

  /* Go through pending send request list and cancel them all */
  while ((CurrentEntry = ExInterlockedRemoveHeadList(&AddrFile->ReceiveQueue, &AddrFile->Lock))) {
    SendRequest = CONTAINING_RECORD(CurrentEntry, DATAGRAM_SEND_REQUEST, ListEntry);
    (*SendRequest->Complete)(SendRequest->Context, STATUS_CANCELLED, 0);
    ExFreePoolWithTag(SendRequest, DATAGRAM_SEND_TAG);
  }

  /* Protocol specific handling */
  switch (AddrFile->Protocol) {
  case IPPROTO_TCP:
    if (AddrFile->Port)
    {
        TCPFreePort(AddrFile->Port);
    }
    break;

  case IPPROTO_UDP:
    UDPFreePort( AddrFile->Port );
    break;
  }

  RemoveEntityByContext(AddrFile);

  ExFreePoolWithTag(Object, ADDR_FILE_TAG);
}