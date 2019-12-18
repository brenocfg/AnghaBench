#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Free; } ;
typedef  TYPE_1__* PIP_PACKET ;
typedef  int /*<<< orphan*/  IP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  DeinitializePacket ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 

PIP_PACKET IPInitializePacket(
    PIP_PACKET IPPacket,
    ULONG Type)
/*
 * FUNCTION: Creates an IP packet object
 * ARGUMENTS:
 *     Type = Type of IP packet
 * RETURNS:
 *     Pointer to the created IP packet. NULL if there was not enough free resources.
 */
{
    RtlZeroMemory(IPPacket, sizeof(IP_PACKET));

    IPPacket->Free     = DeinitializePacket;
    IPPacket->Type     = Type;

    return IPPacket;
}