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
typedef  scalar_t__ UCHAR ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_CURSOR ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_CURSOR ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PACKET_TYPE_CURSOR ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bCursorEnabled ; 
 scalar_t__ packet ; 

void HideCursorSerial(void)
{
    PSERIAL_DATA_PACKET_CURSOR pCursor;
    PSERIAL_PACKET p;

    ENTER_FUNC();

    bCursorEnabled = FALSE;

    pCursor = (PSERIAL_DATA_PACKET_CURSOR)packet;
    pCursor->type = PACKET_TYPE_CURSOR;
    pCursor->state = (UCHAR)TRUE;

    p = AssemblePacket((PUCHAR)pCursor,sizeof(SERIAL_DATA_PACKET_CURSOR));
    SendPacket(p);

    LEAVE_FUNC();
}