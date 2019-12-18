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
typedef  int ULONG ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_5__ {scalar_t__ Type; TYPE_1__ Address; } ;
typedef  TYPE_2__* PIP_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DATALINK ; 
 scalar_t__ IP_ADDRESS_V4 ; 
 int IPv4NToHl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

UINT AddrCountPrefixBits( PIP_ADDRESS Netmask ) {
    UINT Prefix = 0;
    if( Netmask->Type == IP_ADDRESS_V4 ) {
	ULONG BitTest = 0x80000000;

	/* The mask has been read in network order.  Put it in host order
	 * in order to scan it. */

	ULONG TestMask = IPv4NToHl(Netmask->Address.IPv4Address);

	while( (BitTest & TestMask) == BitTest ) {
	    Prefix++;
	    BitTest >>= 1;
	}
	return Prefix;
    } else {
	TI_DbgPrint(DEBUG_DATALINK, ("Don't know address type %d\n",
				     Netmask->Type));
	return 0;
    }
}