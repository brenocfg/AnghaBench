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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PTRANSPORT_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TaLengthOfTransportAddress (int /*<<< orphan*/ ) ; 

VOID TaCopyTransportAddressInPlace( PTRANSPORT_ADDRESS Target,
                                    PTRANSPORT_ADDRESS Source ) {
    UINT AddrLen = TaLengthOfTransportAddress( Source );
    RtlCopyMemory( Target, Source, AddrLen );
}