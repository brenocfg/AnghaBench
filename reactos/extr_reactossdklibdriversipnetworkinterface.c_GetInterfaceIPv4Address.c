#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_17__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_18__ {TYPE_7__ Address; } ;
struct TYPE_15__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_16__ {TYPE_5__ Address; } ;
struct TYPE_13__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_14__ {TYPE_3__ Address; } ;
struct TYPE_11__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_12__ {TYPE_1__ Address; } ;
struct TYPE_19__ {TYPE_8__ PointToPoint; TYPE_6__ Broadcast; TYPE_4__ Netmask; TYPE_2__ Unicast; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_9__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
#define  ADE_ADDRMASK 131 
#define  ADE_BROADCAST 130 
#define  ADE_POINTOPOINT 129 
#define  ADE_UNICAST 128 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NTSTATUS GetInterfaceIPv4Address( PIP_INTERFACE Interface,
				  ULONG TargetType,
				  PULONG Address ) {
    switch( TargetType ) {
    case ADE_UNICAST:
	*Address = Interface->Unicast.Address.IPv4Address;
	break;

    case ADE_ADDRMASK:
	*Address = Interface->Netmask.Address.IPv4Address;
	break;

    case ADE_BROADCAST:
	*Address = Interface->Broadcast.Address.IPv4Address;
	break;

    case ADE_POINTOPOINT:
	*Address = Interface->PointToPoint.Address.IPv4Address;
	break;

    default:
	return STATUS_UNSUCCESSFUL;
    }

    return STATUS_SUCCESS;
}