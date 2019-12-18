#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Lock; TYPE_1__* Cache; } ;
struct TYPE_8__ {int /*<<< orphan*/  Address; } ;
struct TYPE_7__ {scalar_t__ EventCount; int /*<<< orphan*/  Address; struct TYPE_7__* Next; } ;
typedef  int* PULONG ;
typedef  TYPE_1__* PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (TYPE_2__*) ; 
 scalar_t__ AddrIsEqual (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 int NB_HASHMASK ; 
 TYPE_3__* NeighborCache ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID
NBResetNeighborTimeout(PIP_ADDRESS Address)
{
    KIRQL OldIrql;
    UINT HashValue;
    PNEIGHBOR_CACHE_ENTRY NCE;

    TI_DbgPrint(DEBUG_NCACHE, ("Resetting NCE timout for 0x%s\n", A2S(Address)));

    HashValue  = *(PULONG)(&Address->Address);
    HashValue ^= HashValue >> 16;
    HashValue ^= HashValue >> 8;
    HashValue ^= HashValue >> 4;
    HashValue &= NB_HASHMASK;

    TcpipAcquireSpinLock(&NeighborCache[HashValue].Lock, &OldIrql);

    for (NCE = NeighborCache[HashValue].Cache;
         NCE != NULL;
         NCE = NCE->Next)
    {
         if (AddrIsEqual(Address, &NCE->Address))
         {
             NCE->EventCount = 0;
             break;
         }
    }

    TcpipReleaseSpinLock(&NeighborCache[HashValue].Lock, OldIrql);
}