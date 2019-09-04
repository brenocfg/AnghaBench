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
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/ * HDSKSPC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DRIVE ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FILEOP_COPY ; 
 int /*<<< orphan*/  FILEOP_DELETE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SPDSL_IGNORE_DISK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetupAddToDiskSpaceListA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 int SetupQuerySpaceRequiredOnDriveA (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  debugstr_longlong (int) ; 
 int get_file_size (char*) ; 
 scalar_t__ is_win9x ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetupQuerySpaceRequiredOnDriveA(void)
{
    BOOL ret;
    HDSKSPC handle;
    LONGLONG space;
    char windir[MAX_PATH];
    char drive[3];
    char tmp[MAX_PATH];
    LONGLONG size;

    if (is_win9x)
        win_skip("SetupQuerySpaceRequiredOnDriveA crashes with NULL disk space handle on Win9x\n");
    else
    {
        SetLastError(0xdeadbeef);
        ret = SetupQuerySpaceRequiredOnDriveA(NULL, NULL, NULL, NULL, 0);
        ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
           GetLastError());

        SetLastError(0xdeadbeef);
        space = 0xdeadbeef;
        ret = SetupQuerySpaceRequiredOnDriveA(NULL, NULL, &space, NULL, 0);
        ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
        ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
           GetLastError());

        SetLastError(0xdeadbeef);
        ret = SetupQuerySpaceRequiredOnDriveA(NULL, "", NULL, NULL, 0);
        ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
        ok(GetLastError() == ERROR_INVALID_HANDLE,
           "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
           GetLastError());

        SetLastError(0xdeadbeef);
        space = 0xdeadbeef;
        ret = SetupQuerySpaceRequiredOnDriveA(NULL, "", &space, NULL, 0);
        ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
        ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
        ok(GetLastError() == ERROR_INVALID_HANDLE,
           "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
           GetLastError());
    }

    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveA(handle, NULL, NULL, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_INVALID_DRIVE, /* Win9x */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, NULL, &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_INVALID_DRIVE, /* Win9x */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveA(handle, "", NULL, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_DRIVE,
       "Expected GetLastError() to return ERROR_INVALID_DRIVE, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, "", &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveA to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_DRIVE,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    GetWindowsDirectoryA(windir, MAX_PATH);
    drive[0] = windir[0]; drive[1] = windir[1]; drive[2] = 0;

    snprintf(tmp, MAX_PATH, "%c:\\wine-test-should-not-exist.txt", drive[0]);
    ret = SetupAddToDiskSpaceListA(handle, tmp, 0x100000, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0x100000, "Expected 0x100000 as required space, got %s\n", debugstr_longlong(space));

    /* adding the same file again doesn't sum up the size */
    ret = SetupAddToDiskSpaceListA(handle, tmp, 0x200000, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0x200000, "Expected 0x200000 as required space, got %s\n", debugstr_longlong(space));

    /* the device doesn't need to exist */
    snprintf(tmp, MAX_PATH, "F:\\wine-test-should-not-exist.txt");
    ret = SetupAddToDiskSpaceListA(handle, tmp, 0x200000, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupQuerySpaceRequiredOnDriveA(handle, "F:", &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0x200000, "Expected 0x200000 as required space, got %s\n", debugstr_longlong(space));

    snprintf(tmp, MAX_PATH, "F:\\wine-test-should-not-exist.txt");
    ret = SetupAddToDiskSpaceListA(handle, tmp, 0x200000, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupQuerySpaceRequiredOnDriveA(handle, "F:", &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0x200000, "Expected 0x200000 as required space, got %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");

    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    /* the real size is subtracted unless SPDSL_IGNORE_DISK is specified */
    snprintf(tmp, MAX_PATH, "%s\\regedit.exe", windir);

    size = get_file_size(tmp);
    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0 || broken(space == -0x5000) || broken(space == -0x7000),
       "Expected 0x0 as required space, got %s\n", debugstr_longlong(space));

    ret = SetupAddToDiskSpaceListA(handle, tmp, size + 0x100000, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0x100000 || broken(space == 0xf9000) || broken(space == 0xfb000),
       "Expected 0x100000 as required space, got %s\n", debugstr_longlong(space));

    ret = SetupAddToDiskSpaceListA(handle, tmp, size - 0x1000, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == -0x1000 || broken(space == -0x6000) || broken(space == -0x8000),
       "Expected -0x1000 as required space, got %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");

    /* test FILEOP_DELETE, then FILEOP_COPY */
    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0 || broken(space == -0x5000) || broken(space == -0x7000),
       "Expected 0x0 as required space, got %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");

    /* test FILEOP_COPY, then FILEOP_DELETE */
    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0 || broken(space == -0x5000) || broken(space == -0x7000),
       "Expected 0x0 as required space, got %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");

    /* test FILEOP_DELETE without SPDSL_IGNORE_DISK */
    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space <= -size, "Expected space <= -size, got %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");

    /* test FILEOP_COPY and FILEOP_DELETE with SPDSL_IGNORE_DISK */
    handle = SetupCreateDiskSpaceListA(NULL, 0, SPDSL_IGNORE_DISK);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space == 0, "Expected size = 0, got %s\n", debugstr_longlong(space));

    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");
    ret = SetupAddToDiskSpaceListA(handle, tmp, size, FILEOP_DELETE, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    space = 0;
    ret = SetupQuerySpaceRequiredOnDriveA(handle, drive, &space, NULL, 0);
    ok(ret, "Expected SetupQuerySpaceRequiredOnDriveA to succeed\n");
    ok(space >= size, "Expected size >= %s\n", debugstr_longlong(space));

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");
}