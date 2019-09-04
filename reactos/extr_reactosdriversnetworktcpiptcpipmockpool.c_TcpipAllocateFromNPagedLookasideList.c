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
struct TYPE_3__ {int /*<<< orphan*/  Size; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PNPAGED_LOOKASIDE_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  PoolAllocateBuffer (int /*<<< orphan*/ ) ; 

PVOID TcpipAllocateFromNPagedLookasideList( PNPAGED_LOOKASIDE_LIST List ) {
    return PoolAllocateBuffer( List->Size );
}