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
struct TYPE_2__ {int /*<<< orphan*/  line; int /*<<< orphan*/  bkcol; int /*<<< orphan*/  fgcol; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_CLRLINE ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_CLRLINE ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_TYPE_CLRLINE ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eBackgroundColor ; 
 int /*<<< orphan*/  eForegroundColor ; 
 scalar_t__ packet ; 

void ClrLineSerial(ULONG line)
{
    PSERIAL_DATA_PACKET_CLRLINE pClrLine;
    PSERIAL_PACKET p;

    pClrLine = (PSERIAL_DATA_PACKET_CLRLINE)packet;
    pClrLine->type = PACKET_TYPE_CLRLINE;
    pClrLine->fgcol = eForegroundColor;
    pClrLine->bkcol = eBackgroundColor;
    pClrLine->line = line;

    p = AssemblePacket((PUCHAR)pClrLine,sizeof(SERIAL_DATA_PACKET_CLRLINE));
    SendPacket(p);
}