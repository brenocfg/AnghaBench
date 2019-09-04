#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * PTRANSPORT_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  TAG_AFD_TRANSPORT_ADDRESS ; 
 int /*<<< orphan*/  TaCopyTransportAddressInPlace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TaLengthOfTransportAddress (int /*<<< orphan*/ *) ; 

PTRANSPORT_ADDRESS TaCopyTransportAddress( PTRANSPORT_ADDRESS OtherAddress ) {
    UINT AddrLen;
    PTRANSPORT_ADDRESS A;

    AddrLen = TaLengthOfTransportAddress( OtherAddress );
    if (!AddrLen)
        return NULL;

    A = ExAllocatePoolWithTag(NonPagedPool,
                              AddrLen,
                              TAG_AFD_TRANSPORT_ADDRESS);

    if( A )
        TaCopyTransportAddressInPlace( A, OtherAddress );

    return A;
}