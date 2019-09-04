#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_14__ {int /*<<< orphan*/ * DirectoryTableBase; } ;
struct TYPE_18__ {TYPE_1__ Pcb; } ;
struct TYPE_15__ {int Valid; int /*<<< orphan*/  PageFrameNumber; } ;
struct TYPE_16__ {scalar_t__ Long; TYPE_2__ Hard; } ;
struct TYPE_17__ {TYPE_3__ u; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_4__* PMMPDE ;
typedef  int /*<<< orphan*/  PFN_NUMBER ;
typedef  TYPE_5__* PEPROCESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBG_UNREFERENCED_LOCAL_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DemandZeroPde ; 
 scalar_t__ FALSE ; 
 scalar_t__ KeAreAllApcsDisabled () ; 
 int /*<<< orphan*/  KeBugCheck (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_MANAGEMENT ; 
 int /*<<< orphan*/  MI_WRITE_INVALID_PTE (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* MiAddressToPde (scalar_t__) ; 
 scalar_t__ MiAddressToPte (scalar_t__) ; 
 int MiAddressToPteOffset (scalar_t__) ; 
 int /*<<< orphan*/  MiDispatchFault (int,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,scalar_t__,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MiFillSystemPageDirectory (scalar_t__,int /*<<< orphan*/ ) ; 
 int MiGetPdeOffset (scalar_t__) ; 
 int /*<<< orphan*/  MiSynchronizeSystemPde (TYPE_4__*) ; 
 void* MmCreateHyperspaceMapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmDeleteHyperspaceMapping (TYPE_4__*) ; 
 scalar_t__ MmSystemRangeStart ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTE_TO_PFN (int /*<<< orphan*/ ) ; 
 TYPE_5__* PsGetCurrentProcess () ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static PULONG
MmGetPageTableForProcess(PEPROCESS Process, PVOID Address, BOOLEAN Create)
{
    PFN_NUMBER Pfn;
    PULONG Pt;
    PMMPDE PointerPde;

    if (Address < MmSystemRangeStart)
    {
        /* We should have a process for user land addresses */
        ASSERT(Process != NULL);

        if(Process != PsGetCurrentProcess())
        {
            PMMPDE PdeBase;
            ULONG PdeOffset = MiGetPdeOffset(Address);

            /* Nobody but page fault should ask for creating the PDE,
             * Which imples that Process is the current one */
            ASSERT(Create == FALSE);

            PdeBase = MmCreateHyperspaceMapping(PTE_TO_PFN(Process->Pcb.DirectoryTableBase[0]));
            if (PdeBase == NULL)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
            PointerPde = PdeBase + PdeOffset;
            if (PointerPde->u.Hard.Valid == 0)
            {
                MmDeleteHyperspaceMapping(PdeBase);
                return NULL;
            }
            else
            {
                Pfn = PointerPde->u.Hard.PageFrameNumber;
            }
            MmDeleteHyperspaceMapping(PdeBase);
            Pt = MmCreateHyperspaceMapping(Pfn);
            if (Pt == NULL)
            {
                KeBugCheck(MEMORY_MANAGEMENT);
            }
            return Pt + MiAddressToPteOffset(Address);
        }
        /* This is for our process */
        PointerPde = MiAddressToPde(Address);
        Pt = (PULONG)MiAddressToPte(Address);
        if (PointerPde->u.Hard.Valid == 0)
        {
            NTSTATUS Status;
            if (Create == FALSE)
            {
                return NULL;
            }
            ASSERT(PointerPde->u.Long == 0);

            MI_WRITE_INVALID_PTE(PointerPde, DemandZeroPde);
            // Tiny HACK: Parameter 1 is the architecture specific FaultCode for an access violation (i.e. page is present)
            Status = MiDispatchFault(0x1,
                                     Pt,
                                     PointerPde,
                                     NULL,
                                     FALSE,
                                     PsGetCurrentProcess(),
                                     NULL,
                                     NULL);
            DBG_UNREFERENCED_LOCAL_VARIABLE(Status);
            ASSERT(KeAreAllApcsDisabled() == TRUE);
            ASSERT(PointerPde->u.Hard.Valid == 1);
        }
        return (PULONG)MiAddressToPte(Address);
    }

    /* This is for kernel land address */
    ASSERT(Process == NULL);
    PointerPde = MiAddressToPde(Address);
    Pt = (PULONG)MiAddressToPte(Address);
    if (PointerPde->u.Hard.Valid == 0)
    {
        /* Let ARM3 synchronize the PDE */
        if(!MiSynchronizeSystemPde(PointerPde))
        {
            /* PDE (still) not valid, let ARM3 allocate one if asked */
            if(Create == FALSE)
                return NULL;
            MiFillSystemPageDirectory(Address, PAGE_SIZE);
        }
    }
    return Pt;
}