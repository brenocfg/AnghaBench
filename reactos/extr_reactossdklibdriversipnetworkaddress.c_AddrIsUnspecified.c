#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int IPv4Address; } ;
struct TYPE_5__ {int Type; TYPE_1__ Address; } ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
#define  IP_ADDRESS_V4 129 
#define  IP_ADDRESS_V6 128 

BOOLEAN AddrIsUnspecified(
    PIP_ADDRESS Address)
/*
 * FUNCTION: Return wether IP address is an unspecified address
 * ARGUMENTS:
 *     Address = Pointer to an IP address structure
 * RETURNS:
 *     TRUE if the IP address is an unspecified address, FALSE if not
 */
{
    switch (Address->Type) {
        case IP_ADDRESS_V4:
            return (Address->Address.IPv4Address == 0 ||
                    Address->Address.IPv4Address == 0xFFFFFFFF);

        case IP_ADDRESS_V6:
        /* FIXME: IPv6 is not supported */
        default:
            return FALSE;
    }
}