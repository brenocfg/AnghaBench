#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_6__ {int Type; TYPE_1__ Address; } ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  DN2H (int /*<<< orphan*/ ) ; 
 int FALSE ; 
#define  IP_ADDRESS_V4 129 
#define  IP_ADDRESS_V6 128 

INT AddrCompare(
    PIP_ADDRESS Address1,
    PIP_ADDRESS Address2)
{
    switch (Address1->Type) {
        case IP_ADDRESS_V4: {
            ULONG Addr1, Addr2;
            if (Address2->Type == IP_ADDRESS_V4) {
                Addr1 = DN2H(Address1->Address.IPv4Address);
                Addr2 = DN2H(Address2->Address.IPv4Address);
                if (Addr1 < Addr2)
                    return -1;
                else
                    if (Addr1 == Addr2)
                        return 0;
                    else
                        return 1;
            } else
                /* FIXME: Support IPv6 */
                return -1;

        case IP_ADDRESS_V6:
            /* FIXME: Support IPv6 */
        break;
        }
    }

    return FALSE;
}