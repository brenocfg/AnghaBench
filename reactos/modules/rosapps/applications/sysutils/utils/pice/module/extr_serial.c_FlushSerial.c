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
struct TYPE_2__ {int /*<<< orphan*/  string; int /*<<< orphan*/  bkcol; int /*<<< orphan*/  fgcol; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_PRINT ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_PRINT ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_TYPE_PRINT ; 
 int /*<<< orphan*/  PICE_strcpy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ PICE_strlen (scalar_t__*) ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eBackgroundColor ; 
 int /*<<< orphan*/  eForegroundColor ; 
 scalar_t__* flush_buffer ; 
 int /*<<< orphan*/  g_x ; 
 int /*<<< orphan*/  g_y ; 
 scalar_t__ packet ; 
 scalar_t__ ulFlushBufferPos ; 

void FlushSerial(void)
{
    PSERIAL_DATA_PACKET_PRINT pPrint;
    PSERIAL_PACKET p;

    pPrint = (PSERIAL_DATA_PACKET_PRINT)packet;
    pPrint->type = PACKET_TYPE_PRINT;
    pPrint->x = g_x;
    pPrint->y = g_y;
    pPrint->fgcol = eForegroundColor;
    pPrint->bkcol = eBackgroundColor;
    flush_buffer[ulFlushBufferPos++] = 0;
    PICE_strcpy(pPrint->string,flush_buffer);
    ulFlushBufferPos = 0;

    p = AssemblePacket((PUCHAR)pPrint,sizeof(SERIAL_DATA_PACKET_PRINT)+PICE_strlen(flush_buffer));
    SendPacket(p);
}