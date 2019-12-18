#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_6__ {int Type; TYPE_2__ Address; } ;
typedef  TYPE_1__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  IPv6_RAW_ADDRESS ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int FALSE ; 
#define  IP_ADDRESS_V4 129 
#define  IP_ADDRESS_V6 128 
 int RtlCompareMemory (TYPE_2__*,TYPE_2__*,int) ; 

BOOLEAN AddrIsEqual(
    PIP_ADDRESS Address1,
    PIP_ADDRESS Address2)
{
    if (Address1->Type != Address2->Type) {
        DbgPrint("AddrIsEqual: Unequal Address Types\n");
        return FALSE;
    }

    switch (Address1->Type) {
        case IP_ADDRESS_V4:
            return (Address1->Address.IPv4Address == Address2->Address.IPv4Address);

        case IP_ADDRESS_V6:
            return (RtlCompareMemory(&Address1->Address, &Address2->Address,
                sizeof(IPv6_RAW_ADDRESS)) == sizeof(IPv6_RAW_ADDRESS));
            break;

        default:
            DbgPrint("AddrIsEqual: Bad address type\n");
            break;
    }

    return FALSE;
}