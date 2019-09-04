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
typedef  int /*<<< orphan*/ * HDSKSPC ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 unsigned int SPDSL_IGNORE_DISK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SetupDuplicateDiskSpaceListA (int /*<<< orphan*/ *,void*,int,unsigned int) ; 
 scalar_t__ is_win9x ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetupDuplicateDiskSpaceListA(void)
{
    HDSKSPC handle, duplicate;

    if (is_win9x)
        win_skip("SetupDuplicateDiskSpaceListA crashes with NULL disk space handle on Win9x\n");
    else
    {
        SetLastError(0xdeadbeef);
        duplicate = SetupDuplicateDiskSpaceListA(NULL, NULL, 0, 0);
        ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
        ok(GetLastError() == ERROR_INVALID_HANDLE,
           "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n", GetLastError());

        SetLastError(0xdeadbeef);
        duplicate = SetupDuplicateDiskSpaceListA(NULL, (void *)0xdeadbeef, 0, 0);
        ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

        SetLastError(0xdeadbeef);
        duplicate = SetupDuplicateDiskSpaceListA(NULL, NULL, 0xdeadbeef, 0);
        ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

        SetLastError(0xdeadbeef);
        duplicate = SetupDuplicateDiskSpaceListA(NULL, NULL, 0, ~0U);
        ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());
    }

    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    if (!handle)
    {
        skip("Failed to create a disk space handle\n");
        return;
    }

    SetLastError(0xdeadbeef);
    duplicate = SetupDuplicateDiskSpaceListA(handle, (void *)0xdeadbeef, 0, 0);
    ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    duplicate = SetupDuplicateDiskSpaceListA(handle, NULL, 0xdeadbeef, 0);
    ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    duplicate = SetupDuplicateDiskSpaceListA(handle, NULL, 0, SPDSL_IGNORE_DISK);
    ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    duplicate = SetupDuplicateDiskSpaceListA(handle, NULL, 0, ~0U);
    ok(!duplicate, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    duplicate = SetupDuplicateDiskSpaceListA(handle, NULL, 0, 0);
    ok(duplicate != NULL, "Expected SetupDuplicateDiskSpaceList to return NULL, got %p\n", duplicate);
    ok(duplicate != handle,
       "Expected new handle (%p) to be different from the old handle (%p)\n", duplicate, handle);

    ok(SetupDestroyDiskSpaceList(duplicate), "Expected SetupDestroyDiskSpaceList to succeed\n");
    ok(SetupDestroyDiskSpaceList(handle), "Expected SetupDestroyDiskSpaceList to succeed\n");
}