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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FILEOP_COPY ; 
 int /*<<< orphan*/  FILEOP_RENAME ; 
 int /*<<< orphan*/  GetLastError () ; 
 int SetupAddToDiskSpaceListA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetupAddToDiskSpaceListA(void)
{
    HDSKSPC handle;
    BOOL ret;

    ret = SetupAddToDiskSpaceListA(NULL, "C:\\some-file.dat", 0, FILEOP_COPY, 0, 0);
    ok(!ret, "Expected SetupAddToDiskSpaceListA to return FALSE, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_HANDLE,
       "Expected GetLastError() to return ERROR_INVALID_HANDLE, got %u\n", GetLastError());

    handle = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(handle != NULL,"Expected SetupCreateDiskSpaceListA to return a valid handle\n");

    ret = SetupAddToDiskSpaceListA(handle, NULL, 0, FILEOP_COPY, 0, 0);
    ok(ret || broken(!ret) /* >= Vista */, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(handle, "C:\\some-file.dat", -20, FILEOP_COPY, 0, 0);
    ok(ret, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(handle, "C:\\some-file.dat", 0, FILEOP_RENAME, 0, 0);
    ok(!ret, "Expected SetupAddToDiskSpaceListA to return FALSE\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    ret = SetupAddToDiskSpaceListA(handle, NULL, 0, FILEOP_RENAME, 0, 0);
    ok(ret || broken(!ret) /* >= Vista */, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ret = SetupAddToDiskSpaceListA(NULL, NULL, 0, FILEOP_RENAME, 0, 0);
    ok(ret || broken(!ret) /* >= Vista */, "Expected SetupAddToDiskSpaceListA to succeed\n");

    ok(SetupDestroyDiskSpaceList(handle),
       "Expected SetupDestroyDiskSpaceList to succeed\n");
}