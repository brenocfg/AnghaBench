#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ULONG ;
struct TYPE_11__ {int Length; int DataTransferLength; int TimeOutValue; int DataBufferOffset; int /*<<< orphan*/ * CurrentTaskFile; int /*<<< orphan*/  AtaFlags; } ;
struct TYPE_10__ {int NominalMediaRotationRate; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  TYPE_1__ IDENTIFY_DEVICE_DATA ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ATA_PASS_THROUGH_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAGS_DATA_IN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  IDE_COMMAND_IDENTIFY ; 
 int /*<<< orphan*/  IOCTL_ATA_PASS_THROUGH ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,TYPE_2__*,int) ; 
 TYPE_2__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static BOOL is_ssd(HANDLE h) {
    ULONG aptelen;
    ATA_PASS_THROUGH_EX* apte;
    IO_STATUS_BLOCK iosb;
    NTSTATUS Status;
    IDENTIFY_DEVICE_DATA* idd;

    aptelen = sizeof(ATA_PASS_THROUGH_EX) + 512;
#ifndef __REACTOS__
    apte = malloc(aptelen);

    RtlZeroMemory(apte, aptelen);
#else
    apte = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, aptelen);
#endif

    apte->Length = sizeof(ATA_PASS_THROUGH_EX);
    apte->AtaFlags = ATA_FLAGS_DATA_IN;
    apte->DataTransferLength = aptelen - sizeof(ATA_PASS_THROUGH_EX);
    apte->TimeOutValue = 3;
    apte->DataBufferOffset = apte->Length;
    apte->CurrentTaskFile[6] = IDE_COMMAND_IDENTIFY;

    Status = NtDeviceIoControlFile(h, NULL, NULL, NULL, &iosb, IOCTL_ATA_PASS_THROUGH, apte, aptelen, apte, aptelen);

    if (NT_SUCCESS(Status)) {
        idd = (IDENTIFY_DEVICE_DATA*)((uint8_t*)apte + sizeof(ATA_PASS_THROUGH_EX));

        if (idd->NominalMediaRotationRate == 1) {
#ifndef __REACTOS__
            free(apte);
#else
            RtlFreeHeap(RtlGetProcessHeap(), 0, apte);
#endif
            return TRUE;
        }
    }

#ifndef __REACTOS__
    free(apte);
#else
    RtlFreeHeap(RtlGetProcessHeap(), 0, apte);
#endif

    return FALSE;
}