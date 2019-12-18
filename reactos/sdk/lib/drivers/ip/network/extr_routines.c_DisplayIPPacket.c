#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  HeaderSize; int /*<<< orphan*/  Header; int /*<<< orphan*/  NdisPacket; int /*<<< orphan*/  TotalSize; } ;
typedef  TYPE_1__* PIP_PACKET ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int DEBUG_IP ; 
 int DEBUG_PBUFFER ; 
 int DPFLTR_MASK ; 
 int /*<<< orphan*/  DPFLTR_TCPIP_ID ; 
 scalar_t__ DbgQueryDebugFilterState (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DisplayIPHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 

VOID DisplayIPPacket(
    PIP_PACKET IPPacket)
{
#if DBG
    UINT Length;
    PCHAR CharBuffer;

    /* DbgQueryDebugFilterState returns (NTSTATUS)TRUE, (NTSTATUS)FALSE or a failure status code */
    if ((DbgQueryDebugFilterState(DPFLTR_TCPIP_ID, DEBUG_PBUFFER | DPFLTR_MASK) != (NTSTATUS)TRUE) ||
        (DbgQueryDebugFilterState(DPFLTR_TCPIP_ID, DEBUG_IP | DPFLTR_MASK) != (NTSTATUS)TRUE)) {
        return;
    }

    if (!IPPacket) {
        TI_DbgPrint(MIN_TRACE, ("Cannot display null packet.\n"));
        return;
    }

    TI_DbgPrint(MIN_TRACE, ("IPPacket is at (0x%X).\n", IPPacket));
    TI_DbgPrint(MIN_TRACE, ("Header buffer is at (0x%X).\n", IPPacket->Header));
    TI_DbgPrint(MIN_TRACE, ("Header size is (%d).\n", IPPacket->HeaderSize));
    TI_DbgPrint(MIN_TRACE, ("TotalSize (%d).\n", IPPacket->TotalSize));
    TI_DbgPrint(MIN_TRACE, ("NdisPacket (0x%X).\n", IPPacket->NdisPacket));

    CharBuffer = IPPacket->Header;
    Length = IPPacket->HeaderSize;
    DisplayIPHeader(CharBuffer, Length);
#endif
}