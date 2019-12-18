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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ OwnerPsp; } ;
typedef  TYPE_1__* PDOS_MCB ;

/* Variables and functions */
 TYPE_1__* SEGMENT_TO_MCB (scalar_t__) ; 

VOID DosChangeMemoryOwner(WORD Segment, WORD NewOwner)
{
    PDOS_MCB Mcb = SEGMENT_TO_MCB(Segment - 1);
    Mcb->OwnerPsp = NewOwner;
}