#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
struct TYPE_8__ {scalar_t__ CurrentPsp; } ;
struct TYPE_7__ {int /*<<< orphan*/  RefCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  HandleTablePtr; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  TYPE_2__* PDOS_FILE_DESCRIPTOR ;
typedef  int* LPBYTE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,size_t,size_t) ; 
 int /*<<< orphan*/  DosCloseHandle (size_t) ; 
 TYPE_2__* DosGetFileDescriptor (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAR_POINTER (int /*<<< orphan*/ ) ; 
 TYPE_1__* SEGMENT_TO_PSP (scalar_t__) ; 
 scalar_t__ SYSTEM_PSP ; 
 TYPE_3__* Sda ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DosForceDuplicateHandle(WORD OldHandle, WORD NewHandle)
{
    BYTE DescriptorId;
    PDOS_PSP PspBlock;
    LPBYTE HandleTable;
    PDOS_FILE_DESCRIPTOR Descriptor;

    DPRINT("DosForceDuplicateHandle: OldHandle 0x%04X, NewHandle 0x%04X\n",
           OldHandle,
           NewHandle);

    /* The system PSP has no handle table */
    if (Sda->CurrentPsp == SYSTEM_PSP) return FALSE;

    /* Get a pointer to the handle table */
    PspBlock = SEGMENT_TO_PSP(Sda->CurrentPsp);
    HandleTable = (LPBYTE)FAR_POINTER(PspBlock->HandleTablePtr);

    /* Make sure the old handle is open */
    if (HandleTable[OldHandle] == 0xFF) return FALSE;

    /* Check if the new handle is open */
    if (HandleTable[NewHandle] != 0xFF)
    {
        /* Close it */
        DosCloseHandle(NewHandle);
    }

    DescriptorId = HandleTable[OldHandle];
    Descriptor = DosGetFileDescriptor(DescriptorId);
    if (Descriptor == NULL) return FALSE;

    /* Increment the reference count of the descriptor */
    Descriptor->RefCount++;

    /* Make the new handle point to that descriptor */
    HandleTable[NewHandle] = DescriptorId;

    /* Return success */
    return TRUE;
}