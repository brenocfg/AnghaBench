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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int IPv4Address; } ;
struct TYPE_7__ {scalar_t__ Type; TYPE_1__ Address; } ;
typedef  TYPE_2__* PIP_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DATALINK ; 
 scalar_t__ IP_ADDRESS_V4 ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

VOID AddrWidenAddress( PIP_ADDRESS Network, PIP_ADDRESS Source,
		       PIP_ADDRESS Netmask ) {
    if( Netmask->Type == IP_ADDRESS_V4 ) {
        Network->Type = Netmask->Type;
	Network->Address.IPv4Address =
	    Source->Address.IPv4Address & Netmask->Address.IPv4Address;
    } else {
	TI_DbgPrint(DEBUG_DATALINK, ("Don't know address type %d\n",
				     Netmask->Type));
	*Network = *Source;
    }
}