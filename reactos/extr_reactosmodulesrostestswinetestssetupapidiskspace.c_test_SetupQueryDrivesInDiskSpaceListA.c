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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/ * HDSKSPC ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FILEOP_COPY ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SPDSL_IGNORE_DISK ; 
 int SetupAddToDiskSpaceListA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 int SetupQueryDrivesInDiskSpaceListA (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetupQueryDrivesInDiskSpaceListA(void)
{
    char buffer[MAX_PATH];
    HDSKSPC handle;
    DWORD size;
    BOOL ret;

    handle = SetupCreateDiskSpaceListA(NULL, 0, SPDSL_IGNORE_DISK);
    ok(handle != NULL,"Expected SetupCreateDiskSpaceListA to return a valid handle\n");

    ret = SetupQueryDrivesInDiskSpaceListA(handle, NULL, 0, NULL);
    ok(ret, "Expected SetupQueryDrivesInDiskSpaceListA to succeed\n");

    size = 0;
    ret = SetupQueryDrivesInDiskSpaceListA(handle, NULL, 0, &size);
    ok(ret, "Expected SetupQueryDrivesInDiskSpaceListA to succeed\n");
    ok(size == 1, "Expected size 1, got %u\n", size);

    ret = SetupAddToDiskSpaceListA(handle, "F:\\random-file.dat", 0, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(handle, "G:\\random-file.dat", 0, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(handle, "G:\\random-file2.dat", 0, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(handle, "X:\\random-file.dat", 0, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    size = 0;
    ret = SetupQueryDrivesInDiskSpaceListA(handle, NULL, 0, &size);
    ok(ret, "Expected SetupQueryDrivesInDiskSpaceListA to succeed\n");
    ok(size == 10, "Expected size 10, got %u\n", size);

    size = 0;
    ret = SetupQueryDrivesInDiskSpaceListA(handle, buffer, 0, &size);
    ok(!ret, "Expected SetupQueryDrivesInDiskSpaceListA to fail\n");
    ok(size == 4, "Expected size 4, got %u\n", size);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected GetLastError() to return ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());

    size = 0;
    ret = SetupQueryDrivesInDiskSpaceListA(handle, buffer, 4, &size);
    ok(!ret, "Expected SetupQueryDrivesInDiskSpaceListA to fail\n");
    ok(size == 7, "Expected size 7, got %u\n", size);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected GetLastError() to return ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());

    size = 0;
    ret = SetupQueryDrivesInDiskSpaceListA(handle, buffer, 7, &size);
    ok(!ret, "Expected SetupQueryDrivesInDiskSpaceListA to fail\n");
    ok(size == 10, "Expected size 10, got %u\n", size);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected GetLastError() to return ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());

    size = 0;
    memset(buffer, 0xff, sizeof(buffer));
    ret = SetupQueryDrivesInDiskSpaceListA(handle, buffer, sizeof(buffer), &size);
    ok(ret, "Expected SetupQueryDrivesInDiskSpaceListA to succeed\n");
    ok(size == 10, "Expected size 10, got %u\n", size);
    ok(!memcmp("f:\0g:\0x:\0\0", buffer, 10), "Device list does not match\n");

    memset(buffer, 0xff, sizeof(buffer));
    ret = SetupQueryDrivesInDiskSpaceListA(handle, buffer, sizeof(buffer), NULL);
    ok(ret, "Expected SetupQueryDrivesInDiskSpaceListA to succeed\n");
    ok(!memcmp("f:\0g:\0x:\0\0", buffer, 10), "Device list does not match\n");

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");
}