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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ StartingPort; int /*<<< orphan*/  Lock; int /*<<< orphan*/  ProtoBitmap; } ;
typedef  TYPE_1__* PPORT_SET ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlFindClearBits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlSetBit (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ htons (scalar_t__) ; 

ULONG AllocateAnyPort( PPORT_SET PortSet ) {
    ULONG AllocatedPort;
    KIRQL OldIrql;

    KeAcquireSpinLock( &PortSet->Lock, &OldIrql );
    AllocatedPort = RtlFindClearBits( &PortSet->ProtoBitmap, 1, 0 );
    if( AllocatedPort != (ULONG)-1 ) {
	RtlSetBit( &PortSet->ProtoBitmap, AllocatedPort );
	AllocatedPort += PortSet->StartingPort;
	KeReleaseSpinLock( &PortSet->Lock, OldIrql );
	return htons(AllocatedPort);
    }
    KeReleaseSpinLock( &PortSet->Lock, OldIrql );

    return -1;
}