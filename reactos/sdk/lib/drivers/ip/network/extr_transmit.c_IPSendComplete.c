#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  Status; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  TYPE_1__* PIPFRAGMENT_CONTEXT ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID IPSendComplete
(PVOID Context, PNDIS_PACKET NdisPacket, NDIS_STATUS NdisStatus)
/*
 * FUNCTION: IP datagram fragment send completion handler
 * ARGUMENTS:
 *     Context    = Pointer to context information (IP_INTERFACE)
 *     Packet     = Pointer to NDIS packet that was sent
 *     NdisStatus = NDIS status of operation
 * NOTES:
 *    This routine is called when an IP datagram fragment has been sent
 */
{
    PIPFRAGMENT_CONTEXT IFC = (PIPFRAGMENT_CONTEXT)Context;

    TI_DbgPrint
	(MAX_TRACE,
	 ("Called. Context (0x%X)  NdisPacket (0x%X)  NdisStatus (0x%X)\n",
	  Context, NdisPacket, NdisStatus));
	  
	IFC->Status = NdisStatus;
	KeSetEvent(&IFC->Event, 0, FALSE);
}