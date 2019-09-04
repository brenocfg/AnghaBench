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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_INVERTLINE ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_INVERTLINE ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_TYPE_INVERTLINE ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 scalar_t__ packet ; 

void InvertLineSerial(ULONG line)
{
    PSERIAL_DATA_PACKET_INVERTLINE pInvertLine;
    PSERIAL_PACKET p;

    pInvertLine = (PSERIAL_DATA_PACKET_INVERTLINE)packet;
    pInvertLine->type = PACKET_TYPE_INVERTLINE;
    pInvertLine->line = line;

    p = AssemblePacket((PUCHAR)pInvertLine,sizeof(SERIAL_DATA_PACKET_INVERTLINE));
    SendPacket(p);
}