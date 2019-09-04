#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_6__ {int HandleTableSize; int /*<<< orphan*/  HandleTablePtr; scalar_t__ ParentPsp; void* CriticalAddress; void* BreakAddress; void* TerminateAddress; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  void** LPDWORD ;

/* Variables and functions */
 scalar_t__ BaseAddress ; 
 int DEFAULT_JFT_SIZE ; 
 TYPE_1__* FAR_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* SEGMENT_TO_PSP (int /*<<< orphan*/ ) ; 

VOID DosClonePsp(WORD DestSegment, WORD SourceSegment)
{
    PDOS_PSP DestPsp    = SEGMENT_TO_PSP(DestSegment);
    PDOS_PSP SourcePsp  = SEGMENT_TO_PSP(SourceSegment);
    LPDWORD IntVecTable = (LPDWORD)((ULONG_PTR)BaseAddress);

    /* Literally copy the PSP first */
    RtlCopyMemory(DestPsp, SourcePsp, sizeof(*DestPsp));

    /* Save the interrupt vectors */
    DestPsp->TerminateAddress = IntVecTable[0x22];
    DestPsp->BreakAddress     = IntVecTable[0x23];
    DestPsp->CriticalAddress  = IntVecTable[0x24];

    /* No parent PSP */
    DestPsp->ParentPsp = 0;

    /* Set the handle table pointers to the internal handle table */
    DestPsp->HandleTableSize = DEFAULT_JFT_SIZE;
    DestPsp->HandleTablePtr  = MAKELONG(0x18, DestSegment);

    /* Copy the parent handle table without referencing the SFT */
    RtlCopyMemory(FAR_POINTER(DestPsp->HandleTablePtr),
                  FAR_POINTER(SourcePsp->HandleTablePtr),
                  DEFAULT_JFT_SIZE);
}