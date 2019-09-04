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
typedef  void* ULONG ;
struct TYPE_6__ {int Length; int /*<<< orphan*/  RegionListEntry; void* Protect; void* Type; } ;
typedef  int SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PMM_REGION ;
typedef  int /*<<< orphan*/  (* PMM_ALTER_REGION_FUNC ) (int /*<<< orphan*/ ,scalar_t__,int,void*,void*,void*,void*) ;
typedef  int /*<<< orphan*/  PMMSUPPORT ;
typedef  int /*<<< orphan*/  MM_REGION ;

/* Variables and functions */
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertAfterEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_MM_REGION ; 
 int min (int,int) ; 

__attribute__((used)) static PMM_REGION
MmSplitRegion(PMM_REGION InitialRegion, PVOID InitialBaseAddress,
              PVOID StartAddress, SIZE_T Length, ULONG NewType,
              ULONG NewProtect, PMMSUPPORT AddressSpace,
              PMM_ALTER_REGION_FUNC AlterFunc)
{
    PMM_REGION NewRegion1;
    PMM_REGION NewRegion2;
    SIZE_T InternalLength;

    /* Allocate this in front otherwise the failure case is too difficult. */
    NewRegion2 = ExAllocatePoolWithTag(NonPagedPool, sizeof(MM_REGION),
                                       TAG_MM_REGION);
    if (NewRegion2 == NULL)
    {
        return(NULL);
    }

    /* Create the new region. */
    NewRegion1 = ExAllocatePoolWithTag(NonPagedPool, sizeof(MM_REGION),
                                       TAG_MM_REGION);
    if (NewRegion1 == NULL)
    {
        ExFreePoolWithTag(NewRegion2, TAG_MM_REGION);
        return(NULL);
    }
    NewRegion1->Type = NewType;
    NewRegion1->Protect = NewProtect;
    InternalLength = ((char*)InitialBaseAddress + InitialRegion->Length) - (char*)StartAddress;
    InternalLength = min(InternalLength, Length);
    NewRegion1->Length = InternalLength;
    InsertAfterEntry(&InitialRegion->RegionListEntry,
                     &NewRegion1->RegionListEntry);

    /*
     * Call our helper function to do the changes on the addresses contained
     * in the initial region.
     */
    AlterFunc(AddressSpace, StartAddress, InternalLength, InitialRegion->Type,
              InitialRegion->Protect, NewType, NewProtect);

    /*
     * If necessary create a new region for the portion of the initial region
     * beyond the range of addresses to alter.
     */
    if (((char*)InitialBaseAddress + InitialRegion->Length) > ((char*)StartAddress + Length))
    {
        NewRegion2->Type = InitialRegion->Type;
        NewRegion2->Protect = InitialRegion->Protect;
        NewRegion2->Length = ((char*)InitialBaseAddress + InitialRegion->Length) -
                             ((char*)StartAddress + Length);
        InsertAfterEntry(&NewRegion1->RegionListEntry,
                         &NewRegion2->RegionListEntry);
    }
    else
    {
        ExFreePoolWithTag(NewRegion2, TAG_MM_REGION);
    }

    /* Either remove or shrink the initial region. */
    if (InitialBaseAddress == StartAddress)
    {
        RemoveEntryList(&InitialRegion->RegionListEntry);
        ExFreePoolWithTag(InitialRegion, TAG_MM_REGION);
    }
    else
    {
        InitialRegion->Length = (char*)StartAddress - (char*)InitialBaseAddress;
    }

    return(NewRegion1);
}