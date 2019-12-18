#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Type; } ;
struct TYPE_10__ {int AddressType; int /*<<< orphan*/  Address; int /*<<< orphan*/  AddressLength; } ;
struct TYPE_9__ {int /*<<< orphan*/  in_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_8__ {scalar_t__ TAAddressCount; TYPE_3__* Address; } ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  TYPE_1__* PTRANSPORT_ADDRESS ;
typedef  TYPE_2__* PTDI_ADDRESS_IP ;
typedef  TYPE_3__* PTA_ADDRESS ;
typedef  TYPE_4__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  AddrInitIPv4 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_ADDRESS ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TDI_ADDRESS_LENGTH_IP ; 
#define  TDI_ADDRESS_TYPE_IP 128 

NTSTATUS AddrGetAddress(
    PTRANSPORT_ADDRESS AddrList,
    PIP_ADDRESS Address,
    PUSHORT Port)
{
    PTA_ADDRESS CurAddr;
    INT i;

    /* We can only use IP addresses. Search the list until we find one */
    CurAddr = AddrList->Address;

    for (i = 0; i < AddrList->TAAddressCount; i++) {
        switch (CurAddr->AddressType) {
        case TDI_ADDRESS_TYPE_IP:
            if (CurAddr->AddressLength >= TDI_ADDRESS_LENGTH_IP) {
                /* This is an IPv4 address */
                PTDI_ADDRESS_IP ValidAddr = (PTDI_ADDRESS_IP)CurAddr->Address;
                *Port = ValidAddr->sin_port;
		Address->Type = CurAddr->AddressType;
		ValidAddr = (PTDI_ADDRESS_IP)CurAddr->Address;
		AddrInitIPv4(Address, ValidAddr->in_addr);
		return STATUS_SUCCESS;
	    }
	}
    }

    return STATUS_INVALID_ADDRESS;
}