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
typedef  int /*<<< orphan*/  root ;
typedef  int /*<<< orphan*/  device_extension ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {scalar_t__ NextEntryOffset; scalar_t__ EaValueLength; scalar_t__ EaNameLength; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ FILE_FULL_EA_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  EA_EA ; 
 int /*<<< orphan*/  EA_EA_HASH ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCheckEaBufferValidity (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_xattr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ULONG get_ea_len(device_extension* Vcb, root* subvol, UINT64 inode, PIRP Irp) {
    UINT8* eadata;
    UINT16 len;

    if (get_xattr(Vcb, subvol, inode, EA_EA, EA_EA_HASH, &eadata, &len, Irp)) {
        ULONG offset;
        NTSTATUS Status;

        Status = IoCheckEaBufferValidity((FILE_FULL_EA_INFORMATION*)eadata, len, &offset);

        if (!NT_SUCCESS(Status)) {
            WARN("IoCheckEaBufferValidity returned %08x (error at offset %u)\n", Status, offset);
            ExFreePool(eadata);
            return 0;
        } else {
            FILE_FULL_EA_INFORMATION* eainfo;
            ULONG ealen;

            ealen = 4;
            eainfo = (FILE_FULL_EA_INFORMATION*)eadata;
            do {
                ealen += 5 + eainfo->EaNameLength + eainfo->EaValueLength;

                if (eainfo->NextEntryOffset == 0)
                    break;

                eainfo = (FILE_FULL_EA_INFORMATION*)(((UINT8*)eainfo) + eainfo->NextEntryOffset);
            } while (TRUE);

            ExFreePool(eadata);

            return ealen;
        }
    } else
        return 0;
}