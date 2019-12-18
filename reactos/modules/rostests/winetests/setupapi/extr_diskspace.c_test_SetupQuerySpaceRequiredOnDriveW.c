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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/ * HDSKSPC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INVALID_DRIVE ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 scalar_t__ SetupQuerySpaceRequiredOnDriveW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetupQuerySpaceRequiredOnDriveW(void)
{
    static const WCHAR emptyW[] = {0};

    BOOL ret;
    HDSKSPC handle;
    LONGLONG space;

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveW(NULL, NULL, NULL, NULL, 0);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("SetupQuerySpaceRequiredOnDriveW is not available\n");
        return;
    }
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveW(NULL, NULL, &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveW(NULL, emptyW, NULL, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveW(NULL, emptyW, &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n",
       GetLastError());

    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveW(handle, NULL, NULL, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_INVALID_DRIVE, /* NT4/Win2k/XP/Win2k3 */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveW(handle, NULL, &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       GetLastError() == ERROR_INVALID_DRIVE, /* NT4/Win2k/XP/Win2k3 */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupQuerySpaceRequiredOnDriveW(handle, emptyW, NULL, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_DRIVE,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    space = 0xdeadbeef;
    ret = SetupQuerySpaceRequiredOnDriveW(handle, emptyW, &space, NULL, 0);
    ok(!ret, "Expected SetupQuerySpaceRequiredOnDriveW to return FALSE, got %d\n", ret);
    ok(space == 0xdeadbeef, "Expected output space parameter to be untouched\n");
    ok(GetLastError() == ERROR_INVALID_DRIVE,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");
}