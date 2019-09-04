#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ AddressLength; } ;
typedef  TYPE_1__* PTA_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MID_TRACE ; 

UINT TaLengthOfAddress( PTA_ADDRESS Addr )
{
    UINT AddrLen = Addr->AddressLength;

    if (!AddrLen)
        return 0;

    AddrLen += 2 * sizeof( USHORT );

    AFD_DbgPrint(MID_TRACE,("AddrLen %x\n", AddrLen));

    return AddrLen;
}