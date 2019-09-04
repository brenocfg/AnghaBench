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
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int**,int,int**,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_FUNCTION ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*,...) ; 

__attribute__((used)) static void test_disk_extents(void)
{
    BOOL ret;
    DWORD size;
    HANDLE handle;
    static DWORD data[16];

    handle = CreateFileA( "\\\\.\\c:", GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0 );
    if (handle == INVALID_HANDLE_VALUE)
    {
        win_skip("can't open c: drive %u\n", GetLastError());
        return;
    }
    size = 0;
    ret = DeviceIoControl( handle, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, &data,
                           sizeof(data), &data, sizeof(data), &size, NULL );
    if (!ret && GetLastError() == ERROR_INVALID_FUNCTION)
    {
        win_skip("IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS not supported\n");
        CloseHandle( handle );
        return;
    }
    ok(ret, "DeviceIoControl failed %u\n", GetLastError());
    ok(size == 32, "expected 32, got %u\n", size);
    CloseHandle( handle );
}