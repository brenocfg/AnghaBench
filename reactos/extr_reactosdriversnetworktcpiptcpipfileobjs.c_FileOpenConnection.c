#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ConnectionContext; } ;
struct TYPE_5__ {TYPE_1__ Handle; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PTDI_REQUEST ;
typedef  scalar_t__ PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DereferenceObject (scalar_t__) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TCPAllocateConnectionEndpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPSocket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS FileOpenConnection(
  PTDI_REQUEST Request,
  PVOID ClientContext)
{
  NTSTATUS Status;
  PCONNECTION_ENDPOINT Connection;

  TI_DbgPrint(MID_TRACE, ("Called.\n"));

  Connection = TCPAllocateConnectionEndpoint( ClientContext );

  if( !Connection ) return STATUS_NO_MEMORY;

  Status = TCPSocket( Connection, AF_INET, SOCK_STREAM, IPPROTO_TCP );

  if( !NT_SUCCESS(Status) ) {
      DereferenceObject( Connection );
      return Status;
  }

  /* Return connection endpoint file object */
  Request->Handle.ConnectionContext = Connection;

  TI_DbgPrint(MAX_TRACE, ("Leaving.\n"));

  return STATUS_SUCCESS;
}