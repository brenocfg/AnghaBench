#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  FILE_FS_DEVICE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  FileFsDeviceInformation ; 
 int GetLastError () ; 
 int NtQueryVolumeInformationFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int STATUS_ACCESS_VIOLATION ; 
 int STATUS_INFO_LENGTH_MISMATCH ; 
 int STATUS_INVALID_HANDLE ; 
 int STATUS_INVALID_INFO_CLASS ; 
 int STATUS_OBJECT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static
VOID
TestFileFsDeviceInformation(HANDLE handle)
{
    IO_STATUS_BLOCK IoStatusBlock;
    FILE_FS_DEVICE_INFORMATION FileFsDevice;
    NTSTATUS status;

    /*Testing VALID handle, with NULL IN parameters*/
    SetLastError(0xdeadb33f);
    status = NtQueryVolumeInformationFile(handle, NULL, &FileFsDevice, sizeof(FILE_FS_DEVICE_INFORMATION), FileFsDeviceInformation);
    ok(status == STATUS_ACCESS_VIOLATION, "Expected STATUS_ACCESS_VIOLATION, got 0x%lx\n", status);
    ok(GetLastError() == 0xdeadb33f, "Expected 0xdeadb33f, got %lx\n", GetLastError());

    SetLastError(0xcacacaca);
    status = NtQueryVolumeInformationFile(handle,  &IoStatusBlock, NULL, sizeof(FILE_FS_DEVICE_INFORMATION), FileFsDeviceInformation);
    ok(status == STATUS_ACCESS_VIOLATION, "Expected STATUS_ACCESS_VIOLATION, got 0x%lx\n", status);
    ok(GetLastError() == 0xcacacaca, "Expected 0xcacacaca, got %lx\n", GetLastError());

    SetLastError(0xdadadada);
    status = NtQueryVolumeInformationFile(handle,  &IoStatusBlock, &FileFsDevice, 0, FileFsDeviceInformation);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got 0x%lx\n", status);
    ok(GetLastError() == 0xdadadada, "Expected 0xdadadada, got %lx\n", GetLastError());

    /*All valid, invalid FsInformationClass value.*/
    SetLastError(0xdeadbeef);
    status = NtQueryVolumeInformationFile(handle, &IoStatusBlock, &FileFsDevice, sizeof(FILE_FS_DEVICE_INFORMATION), 0);
    ok(status == STATUS_INVALID_INFO_CLASS, "Expected STATUS_INVALID_INFO_CLASS, got 0x%lx\n", status);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %lx\n", GetLastError());

    /*Testing NULL handle*/
    SetLastError(0xdeadbeef);
    status = NtQueryVolumeInformationFile(NULL, &IoStatusBlock, &FileFsDevice, sizeof(FILE_FS_DEVICE_INFORMATION), FileFsDeviceInformation);
    ok(status == STATUS_INVALID_HANDLE, "Expected STATUS_INVALID_HANDLE, got 0x%lx\n", status);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %lx\n", GetLastError());

    /*Testing INVALID_HANDLE_VALUE*/
    SetLastError(0xdeaddead);
    status = NtQueryVolumeInformationFile((HANDLE)(-1), &IoStatusBlock, &FileFsDevice, sizeof(FILE_FS_DEVICE_INFORMATION), FileFsDeviceInformation);
    ok(status == STATUS_OBJECT_TYPE_MISMATCH, "Expected STATUS_OBJECT_TYPE_MISMATCH, got 0x%lx\n", status);
    ok(GetLastError() == 0xdeaddead, "Expected 0xdeaddead, got %lx\n", GetLastError());

    /*Almost all NULL. Then it checks against the Length!*/
    SetLastError(0xdeadbeef);
    status = NtQueryVolumeInformationFile(NULL, NULL, NULL, 0, FileFsDeviceInformation);
    ok(status == STATUS_INFO_LENGTH_MISMATCH, "Expected STATUS_INFO_LENGTH_MISMATCH, got 0x%lx\n", status);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %lx\n", GetLastError());
}