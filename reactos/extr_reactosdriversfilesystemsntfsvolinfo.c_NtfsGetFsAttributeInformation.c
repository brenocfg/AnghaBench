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
struct TYPE_3__ {int FileSystemAttributes; int MaximumComponentNameLength; int FileSystemNameLength; int /*<<< orphan*/  FileSystemName; } ;
typedef  int* PULONG ;
typedef  TYPE_1__* PFILE_FS_ATTRIBUTE_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_FS_ATTRIBUTE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FILE_CASE_PRESERVED_NAMES ; 
 int FILE_READ_ONLY_VOLUME ; 
 int FILE_UNICODE_ON_DISK ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static
NTSTATUS
NtfsGetFsAttributeInformation(PDEVICE_EXTENSION DeviceExt,
                              PFILE_FS_ATTRIBUTE_INFORMATION FsAttributeInfo,
                              PULONG BufferLength)
{
    UNREFERENCED_PARAMETER(DeviceExt);

    DPRINT("NtfsGetFsAttributeInformation()\n");
    DPRINT("FsAttributeInfo = %p\n", FsAttributeInfo);
    DPRINT("BufferLength %lu\n", *BufferLength);
    DPRINT("Required length %lu\n", (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8));

    if (*BufferLength < sizeof (FILE_FS_ATTRIBUTE_INFORMATION))
        return STATUS_INFO_LENGTH_MISMATCH;

    if (*BufferLength < (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8))
        return STATUS_BUFFER_OVERFLOW;

    FsAttributeInfo->FileSystemAttributes =
        FILE_CASE_PRESERVED_NAMES | FILE_UNICODE_ON_DISK | FILE_READ_ONLY_VOLUME;
    FsAttributeInfo->MaximumComponentNameLength = 255;
    FsAttributeInfo->FileSystemNameLength = 8;

    memcpy(FsAttributeInfo->FileSystemName, L"NTFS", 8);

    DPRINT("Finished NtfsGetFsAttributeInformation()\n");

    *BufferLength -= (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8);
    DPRINT("BufferLength %lu\n", *BufferLength);

    return STATUS_SUCCESS;
}