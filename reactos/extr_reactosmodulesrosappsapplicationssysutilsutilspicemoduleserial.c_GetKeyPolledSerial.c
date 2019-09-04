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
struct TYPE_2__ {int /*<<< orphan*/  build_number; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SERIAL_DATA_PACKET_POLL ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PSERIAL_PACKET ;
typedef  TYPE_1__* PSERIAL_DATA_PACKET_POLL ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblePacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_TYPE_POLL ; 
 int /*<<< orphan*/  PICE_BUILD ; 
 int /*<<< orphan*/  PICE_MAJOR_VERSION ; 
 int /*<<< orphan*/  PICE_MINOR_VERSION ; 
 int /*<<< orphan*/  SendPacket (int /*<<< orphan*/ ) ; 
 scalar_t__ packet ; 
 scalar_t__ ucLastKeyRead ; 

UCHAR GetKeyPolledSerial(void)
{
    UCHAR ucResult;
    PSERIAL_DATA_PACKET_POLL pPoll;
    PSERIAL_PACKET p;

    pPoll =                 (PSERIAL_DATA_PACKET_POLL)packet;
    pPoll->type             = PACKET_TYPE_POLL;
    pPoll->major_version    = PICE_MAJOR_VERSION;
    pPoll->minor_version    = PICE_MINOR_VERSION;
    pPoll->build_number     = PICE_BUILD;

    p = AssemblePacket((PUCHAR)pPoll,sizeof(SERIAL_DATA_PACKET_POLL));
    SendPacket(p);

    ucResult = ucLastKeyRead;

    ucLastKeyRead = 0;

    return ucResult;
}