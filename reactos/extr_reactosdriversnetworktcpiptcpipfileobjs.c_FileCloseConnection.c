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
struct TYPE_4__ {int /*<<< orphan*/ * ConnectionContext; } ;
struct TYPE_5__ {TYPE_1__ Handle; } ;
typedef  TYPE_2__* PTDI_REQUEST ;
typedef  int /*<<< orphan*/ * PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TCPClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS FileCloseConnection(
  PTDI_REQUEST Request)
{
  PCONNECTION_ENDPOINT Connection;

  TI_DbgPrint(MID_TRACE, ("Called.\n"));

  Connection = Request->Handle.ConnectionContext;

  if (!Connection) return STATUS_INVALID_PARAMETER;

  TCPClose( Connection );

  Request->Handle.ConnectionContext = NULL;

  TI_DbgPrint(MAX_TRACE, ("Leaving.\n"));

  return STATUS_SUCCESS;
}