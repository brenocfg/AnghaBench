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
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DRIVE_CDROM ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetDriveTypeA (char*) ; 
 char GetLastError () ; 
 int GetLogicalDrives () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  test_dvd_read_structure (scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,char) ; 

__attribute__((used)) static void test_cdrom_ioctl(void)
{
    char drive_letter, drive_path[] = "A:\\", drive_full_path[] = "\\\\.\\A:";
    DWORD bitmask;
    HANDLE handle;

    bitmask = GetLogicalDrives();
    if(!bitmask)
    {
        trace("GetLogicalDrives failed : %u\n", GetLastError());
        return;
    }

    for(drive_letter='A'; drive_letter<='Z'; drive_letter++)
    {
        if(!(bitmask & (1 << (drive_letter-'A') )))
            continue;

        drive_path[0] = drive_letter;
        if(GetDriveTypeA(drive_path) != DRIVE_CDROM)
        {
            trace("Skipping %c:, not a CDROM drive.\n", drive_letter);
            continue;
        }

        trace("Testing with %c:\n", drive_letter);

        drive_full_path[4] = drive_letter;
        handle = CreateFileA(drive_full_path, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
        if(handle == INVALID_HANDLE_VALUE)
        {
            trace("Failed to open the device : %u\n", GetLastError());
            continue;
        }

        /* Add your tests here */
        test_dvd_read_structure(handle);

        CloseHandle(handle);
    }

}