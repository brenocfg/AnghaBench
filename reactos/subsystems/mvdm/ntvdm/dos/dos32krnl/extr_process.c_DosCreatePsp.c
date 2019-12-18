#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_8__ {int /*<<< orphan*/  DosVersion; } ;
struct TYPE_7__ {scalar_t__ CurrentPsp; } ;
struct TYPE_6__ {int* Exit; scalar_t__ LastParagraph; scalar_t__ ParentPsp; int* FarCall; int /*<<< orphan*/  DosVersion; int /*<<< orphan*/  HandleTablePtr; int /*<<< orphan*/  HandleTableSize; int /*<<< orphan*/  HandleTable; int /*<<< orphan*/  EnvBlock; void* CriticalAddress; void* BreakAddress; void* TerminateAddress; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  void** LPDWORD ;

/* Variables and functions */
 scalar_t__ BaseAddress ; 
 int /*<<< orphan*/  DEFAULT_JFT_SIZE ; 
 int /*<<< orphan*/  DosCopyHandleTable (int /*<<< orphan*/ ) ; 
 TYPE_5__* DosData ; 
 int /*<<< orphan*/  MAKELONG (int,scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 TYPE_1__* SEGMENT_TO_PSP (scalar_t__) ; 
 scalar_t__ SYSTEM_PSP ; 
 TYPE_2__* Sda ; 

VOID DosCreatePsp(WORD Segment, WORD ProgramSize)
{
    PDOS_PSP PspBlock   = SEGMENT_TO_PSP(Segment);
    LPDWORD IntVecTable = (LPDWORD)((ULONG_PTR)BaseAddress);

    RtlZeroMemory(PspBlock, sizeof(*PspBlock));

    /* Set the exit interrupt */
    PspBlock->Exit[0] = 0xCD; // int 0x20
    PspBlock->Exit[1] = 0x20;

    /* Set the number of the last paragraph */
    PspBlock->LastParagraph = Segment + ProgramSize;

    /* Save the interrupt vectors */
    PspBlock->TerminateAddress = IntVecTable[0x22];
    PspBlock->BreakAddress     = IntVecTable[0x23];
    PspBlock->CriticalAddress  = IntVecTable[0x24];

    /* Set the parent PSP */
    PspBlock->ParentPsp = Sda->CurrentPsp;

    if (Sda->CurrentPsp != SYSTEM_PSP)
    {
        /* Link to the parent's environment block */
        PspBlock->EnvBlock = SEGMENT_TO_PSP(Sda->CurrentPsp)->EnvBlock;
    }
/*
    else
    {
        PspBlock->EnvBlock = SEG_OFF_TO_PTR(SYSTEM_ENV_BLOCK, 0);
    }
*/

    /* Copy the parent handle table */
    DosCopyHandleTable(PspBlock->HandleTable);

    /* Set the handle table pointers to the internal handle table */
    PspBlock->HandleTableSize = DEFAULT_JFT_SIZE;
    PspBlock->HandleTablePtr  = MAKELONG(0x18, Segment);

    /* Set the DOS version */
    // FIXME: This is here that SETVER stuff enters into action!
    PspBlock->DosVersion = DosData->DosVersion;

    /* Set the far call opcodes */
    PspBlock->FarCall[0] = 0xCD; // int 0x21
    PspBlock->FarCall[1] = 0x21;
    PspBlock->FarCall[2] = 0xCB; // retf
}