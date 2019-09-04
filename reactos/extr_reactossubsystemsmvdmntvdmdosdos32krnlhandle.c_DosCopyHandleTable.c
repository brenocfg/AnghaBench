#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t UINT ;
struct TYPE_17__ {scalar_t__ CurrentPsp; } ;
struct TYPE_16__ {int /*<<< orphan*/  ActiveCon; } ;
struct TYPE_12__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_15__ {int DeviceAttributes; int /*<<< orphan*/  (* OpenRoutine ) (TYPE_4__*) ;TYPE_1__ Name; } ;
struct TYPE_14__ {int DeviceInfo; int /*<<< orphan*/  RefCount; int /*<<< orphan*/  Win32Handle; int /*<<< orphan*/  FileName; int /*<<< orphan*/  DevicePointer; } ;
struct TYPE_13__ {int /*<<< orphan*/  HandleTablePtr; } ;
typedef  TYPE_2__* PDOS_PSP ;
typedef  TYPE_3__* PDOS_FILE_DESCRIPTOR ;
typedef  TYPE_4__* PDOS_DEVICE_NODE ;
typedef  int* LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t DEFAULT_JFT_SIZE ; 
 int /*<<< orphan*/  DPRINT1 (char*,size_t) ; 
 int DosFindDeviceDescriptor (int /*<<< orphan*/ ) ; 
 int DosFindFreeDescriptor () ; 
 int DosFindWin32Descriptor (int /*<<< orphan*/ ) ; 
 TYPE_4__* DosGetDriverNode (int /*<<< orphan*/ ) ; 
 TYPE_3__* DosGetFileDescriptor (int) ; 
 scalar_t__ FAR_POINTER (int /*<<< orphan*/ ) ; 
 int FILE_INFO_DEVICE ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ IsConsoleHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFillMemory (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 TYPE_2__* SEGMENT_TO_PSP (scalar_t__) ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 scalar_t__ SYSTEM_PSP ; 
 TYPE_7__* Sda ; 
 TYPE_6__* SysVars ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

VOID DosCopyHandleTable(LPBYTE DestinationTable)
{
    UINT i;
    PDOS_PSP PspBlock;
    LPBYTE SourceTable;
    PDOS_FILE_DESCRIPTOR Descriptor;

    /* Clear the table first */
    for (i = 0; i < DEFAULT_JFT_SIZE; i++) DestinationTable[i] = 0xFF;

    /* Check if this is the initial process */
    if (Sda->CurrentPsp == SYSTEM_PSP)
    {
        BYTE DescriptorId;
        HANDLE StandardHandles[3];

        /* Get the native standard handles */
        StandardHandles[0] = GetStdHandle(STD_INPUT_HANDLE);
        StandardHandles[1] = GetStdHandle(STD_OUTPUT_HANDLE);
        StandardHandles[2] = GetStdHandle(STD_ERROR_HANDLE);

        for (i = 0; i < 3; i++)
        {
            /* Find the corresponding SFT entry */
            if (IsConsoleHandle(StandardHandles[i]))
            {
                DescriptorId = DosFindDeviceDescriptor(SysVars->ActiveCon);
            }
            else
            {
                DescriptorId = DosFindWin32Descriptor(StandardHandles[i]);
            }

            if (DescriptorId != 0xFF)
            {
                Descriptor = DosGetFileDescriptor(DescriptorId);
            }
            else
            {
                /* Create a new SFT entry for it */
                DescriptorId = DosFindFreeDescriptor();
                if (DescriptorId == 0xFF)
                {
                    DPRINT1("Cannot create standard handle %d, the SFT is full!\n", i);
                    continue;
                }

                Descriptor = DosGetFileDescriptor(DescriptorId);
                ASSERT(Descriptor != NULL);
                RtlZeroMemory(Descriptor, sizeof(*Descriptor));

                if (IsConsoleHandle(StandardHandles[i]))
                {
                    PDOS_DEVICE_NODE Node = DosGetDriverNode(SysVars->ActiveCon);

                    Descriptor->DeviceInfo = Node->DeviceAttributes | FILE_INFO_DEVICE;
                    Descriptor->DevicePointer = SysVars->ActiveCon;
                    RtlFillMemory(Descriptor->FileName, sizeof(Descriptor->FileName), ' ');
                    RtlCopyMemory(Descriptor->FileName, Node->Name.Buffer, Node->Name.Length);

                    /* Call the open routine */
                    if (Node->OpenRoutine) Node->OpenRoutine(Node);
                }
                else
                {
                    Descriptor->Win32Handle = StandardHandles[i];
                }
            }

            Descriptor->RefCount++;
            DestinationTable[i] = DescriptorId;
        }
    }
    else
    {
        /* Get the parent PSP block and handle table */
        PspBlock = SEGMENT_TO_PSP(Sda->CurrentPsp);
        SourceTable = (LPBYTE)FAR_POINTER(PspBlock->HandleTablePtr);

        /* Copy the first 20 handles into the new table */
        for (i = 0; i < DEFAULT_JFT_SIZE; i++)
        {
            Descriptor = DosGetFileDescriptor(SourceTable[i]);
            DestinationTable[i] = SourceTable[i];

            /* Increase the reference count */
            Descriptor->RefCount++;
        }
    }
}