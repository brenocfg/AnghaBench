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
typedef  int /*<<< orphan*/  info ;
typedef  char WCHAR ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
typedef  int UINT64 ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_8__ {TYPE_1__ DiskSize; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ DISK_GEOMETRY_EX ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetDiskFreeSpaceExW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_GEOMETRY_EX ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 

__attribute__((used)) static UINT64 get_freespace( const WCHAR *dir, UINT64 *disksize )
{
    WCHAR root[] = {'\\','\\','.','\\','A',':',0};
    ULARGE_INTEGER free;
    DISK_GEOMETRY_EX info;
    HANDLE handle;
    DWORD bytes_returned;

    free.QuadPart = 512 * 1024 * 1024;
    GetDiskFreeSpaceExW( dir, NULL, NULL, &free );

    root[4] = dir[0];
    handle = CreateFileW( root, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0 );
    if (handle != INVALID_HANDLE_VALUE)
    {
        if (DeviceIoControl( handle, IOCTL_DISK_GET_DRIVE_GEOMETRY_EX, NULL, 0, &info, sizeof(info), &bytes_returned, NULL ))
            *disksize = info.DiskSize.QuadPart;
        CloseHandle( handle );
    }
    return free.QuadPart;
}