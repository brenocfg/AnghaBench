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
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalBufferPool ; 
 int /*<<< orphan*/  GlobalPacketPool ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisAllocateBufferPool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NdisAllocatePacketPool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreePacketPool (int /*<<< orphan*/ ) ; 

NDIS_STATUS InitNdisPools() {
    NDIS_STATUS NdisStatus;
    /* Last argument is extra space size */
    NdisAllocatePacketPool( &NdisStatus, &GlobalPacketPool, 100, 0 );
    if( !NT_SUCCESS(NdisStatus) ) return NdisStatus;

    NdisAllocateBufferPool( &NdisStatus, &GlobalBufferPool, 100 );
    if( !NT_SUCCESS(NdisStatus) )
	NdisFreePacketPool(GlobalPacketPool);

    return NdisStatus;
}