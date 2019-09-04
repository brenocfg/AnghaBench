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
struct TYPE_3__ {scalar_t__ StartingPort; scalar_t__ PortsToOversee; int /*<<< orphan*/  Lock; int /*<<< orphan*/  ProtoBitmap; } ;
typedef  TYPE_1__* PPORT_SET ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlAreBitsClear (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ htons (scalar_t__) ; 

BOOLEAN AllocatePort( PPORT_SET PortSet, ULONG Port ) {
    BOOLEAN Clear;
    KIRQL OldIrql;

    Port = htons(Port);

    if ((Port < PortSet->StartingPort) ||
        (Port >= PortSet->StartingPort + PortSet->PortsToOversee))
    {
       return FALSE;
    }

    Port -= PortSet->StartingPort;

    KeAcquireSpinLock( &PortSet->Lock, &OldIrql );
    Clear = RtlAreBitsClear( &PortSet->ProtoBitmap, Port, 1 );
    if( Clear ) RtlSetBits( &PortSet->ProtoBitmap, Port, 1 );
    KeReleaseSpinLock( &PortSet->Lock, OldIrql );

    return Clear;
}