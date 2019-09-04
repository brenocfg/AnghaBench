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
struct TYPE_6__ {size_t HandleTableSize; int /*<<< orphan*/  HandleTablePtr; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  TYPE_2__* PDOS_FILE_DESCRIPTOR ;
typedef  int* LPBYTE ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 TYPE_2__* DosGetFileDescriptor (int) ; 
 scalar_t__ FAR_POINTER (int /*<<< orphan*/ ) ; 
 size_t INVALID_DOS_HANDLE ; 
 TYPE_1__* SEGMENT_TO_PSP (scalar_t__) ; 
 scalar_t__ SYSTEM_PSP ; 
 TYPE_3__* Sda ; 

WORD DosOpenHandle(BYTE DescriptorId)
{
    WORD DosHandle;
    PDOS_PSP PspBlock;
    LPBYTE HandleTable;
    PDOS_FILE_DESCRIPTOR Descriptor = DosGetFileDescriptor(DescriptorId);

    DPRINT("DosOpenHandle: DescriptorId 0x%02X\n", DescriptorId);

    /* Make sure the descriptor ID is valid */
    if (Descriptor == NULL) return INVALID_DOS_HANDLE;

    /* The system PSP has no handle table */
    if (Sda->CurrentPsp == SYSTEM_PSP) return INVALID_DOS_HANDLE;

    /* Get a pointer to the handle table */
    PspBlock = SEGMENT_TO_PSP(Sda->CurrentPsp);
    HandleTable = (LPBYTE)FAR_POINTER(PspBlock->HandleTablePtr);

    /* Find a free entry in the JFT */
    for (DosHandle = 0; DosHandle < PspBlock->HandleTableSize; DosHandle++)
    {
        if (HandleTable[DosHandle] == 0xFF) break;
    }

    /* If there are no free entries, fail */
    if (DosHandle == PspBlock->HandleTableSize) return INVALID_DOS_HANDLE;

    /* Reference the descriptor */
    Descriptor->RefCount++;

    /* Set the JFT entry to that descriptor ID */
    HandleTable[DosHandle] = DescriptorId;

    /* Return the new handle */
    return DosHandle;
}