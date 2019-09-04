#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
struct TYPE_12__ {scalar_t__ CurrentPsp; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* CloseRoutine ) (TYPE_3__*) ;} ;
struct TYPE_10__ {int DeviceInfo; int /*<<< orphan*/  Win32Handle; int /*<<< orphan*/  DevicePointer; int /*<<< orphan*/  RefCount; } ;
struct TYPE_9__ {int /*<<< orphan*/  HandleTablePtr; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  TYPE_2__* PDOS_FILE_DESCRIPTOR ;
typedef  TYPE_3__* PDOS_DEVICE_NODE ;
typedef  int* LPBYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,size_t) ; 
 TYPE_3__* DosGetDriverNode (int /*<<< orphan*/ ) ; 
 TYPE_2__* DosGetFileDescriptor (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAR_POINTER (int /*<<< orphan*/ ) ; 
 int FILE_INFO_DEVICE ; 
 TYPE_1__* SEGMENT_TO_PSP (scalar_t__) ; 
 scalar_t__ SYSTEM_PSP ; 
 TYPE_5__* Sda ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

BOOLEAN DosCloseHandle(WORD DosHandle)
{
    PDOS_PSP PspBlock;
    LPBYTE HandleTable;
    PDOS_FILE_DESCRIPTOR Descriptor;

    DPRINT("DosCloseHandle: DosHandle 0x%04X\n", DosHandle);

    /* The system PSP has no handle table */
    if (Sda->CurrentPsp == SYSTEM_PSP) return FALSE;

    /* Get a pointer to the handle table */
    PspBlock = SEGMENT_TO_PSP(Sda->CurrentPsp);
    HandleTable = (LPBYTE)FAR_POINTER(PspBlock->HandleTablePtr);

    /* Make sure the handle is open */
    if (HandleTable[DosHandle] == 0xFF) return FALSE;

    /* Make sure the descriptor is valid */
    Descriptor = DosGetFileDescriptor(HandleTable[DosHandle]);
    if (Descriptor == NULL) return FALSE;

    /* Decrement the reference count of the descriptor */
    Descriptor->RefCount--;

    /* Check if the reference count fell to zero */
    if (!Descriptor->RefCount)
    {
        if (Descriptor->DeviceInfo & FILE_INFO_DEVICE)
        {
            PDOS_DEVICE_NODE Node = DosGetDriverNode(Descriptor->DevicePointer);

            /* Call the close routine, if it exists */
            if (Node->CloseRoutine) Node->CloseRoutine(Node);
        }
        else
        {
            /* Close the Win32 handle */
            CloseHandle(Descriptor->Win32Handle);
        }
    }

    /* Clear the entry in the JFT */
    HandleTable[DosHandle] = 0xFF;

    return TRUE;
}