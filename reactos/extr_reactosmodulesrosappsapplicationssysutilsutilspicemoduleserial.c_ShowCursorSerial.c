#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* UCHAR ;
struct TYPE_4__ {scalar_t__ usCurY; scalar_t__ usCurX; } ;
struct TYPE_3__ {void* y; void* x; void* state; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_CURSOR ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_CURSOR ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PACKET_TYPE_CURSOR ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ bCursorEnabled ; 
 scalar_t__ packet ; 
 TYPE_2__* wWindow ; 

void ShowCursorSerial(void)
{
    PSERIAL_DATA_PACKET_CURSOR pCursor;
    PSERIAL_PACKET p;

    ENTER_FUNC();

    bCursorEnabled = TRUE;

    pCursor = (PSERIAL_DATA_PACKET_CURSOR)packet;
    pCursor->type = PACKET_TYPE_CURSOR;
    pCursor->state = (UCHAR)TRUE;
    pCursor->x = (UCHAR)wWindow[OUTPUT_WINDOW].usCurX;
    pCursor->y = (UCHAR)wWindow[OUTPUT_WINDOW].usCurY;

    p = AssemblePacket((PUCHAR)pCursor,sizeof(SERIAL_DATA_PACKET_CURSOR));
    SendPacket(p);

    LEAVE_FUNC();
}