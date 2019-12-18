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
typedef  void* USHORT ;
struct TYPE_2__ {void* ysize; void* xsize; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_CONNECT ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_CONNECT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_TYPE_CONNECT ; 
 int /*<<< orphan*/  SendPacketTimeout (int /*<<< orphan*/ ) ; 
 scalar_t__ packet ; 

BOOLEAN Connect(USHORT xSize,USHORT ySize)
{
    PSERIAL_DATA_PACKET_CONNECT pConnect;
    PSERIAL_PACKET p;

    pConnect = (PSERIAL_DATA_PACKET_CONNECT)packet;
    pConnect->type = PACKET_TYPE_CONNECT;
    pConnect->xsize = xSize;
    pConnect->ysize = ySize;

    p = AssemblePacket((PUCHAR)pConnect,sizeof(SERIAL_DATA_PACKET_CONNECT));
    return SendPacketTimeout(p);
}