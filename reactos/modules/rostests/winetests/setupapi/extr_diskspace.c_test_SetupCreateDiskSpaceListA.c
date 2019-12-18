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
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 unsigned int SPDSL_IGNORE_DISK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * SetupCreateDiskSpaceListA (void*,int,unsigned int) ; 
 int /*<<< orphan*/  SetupDestroyDiskSpaceList (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetupCreateDiskSpaceListA(void)
{
    HDSKSPC ret;

    ret = SetupCreateDiskSpaceListA(NULL, 0, 0);
    ok(ret != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ok(SetupDestroyDiskSpaceList(ret), "Expected SetupDestroyDiskSpaceList to succeed\n");

    ret = SetupCreateDiskSpaceListA(NULL, 0, SPDSL_IGNORE_DISK);
    ok(ret != NULL,
       "Expected SetupCreateDiskSpaceListA to return a valid handle, got NULL\n");

    ok(SetupDestroyDiskSpaceList(ret), "Expected SetupDestroyDiskSpaceList to succeed\n");

    SetLastError(0xdeadbeef);
    ret = SetupCreateDiskSpaceListA(NULL, 0, ~0U);
    ok(ret == NULL ||
       broken(ret != NULL), /* NT4/Win9x/Win2k */
       "Expected SetupCreateDiskSpaceListA to return NULL, got %p\n", ret);
    if (!ret)
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
           GetLastError());
    else
        ok(SetupDestroyDiskSpaceList(ret), "Expected SetupDestroyDiskSpaceList to succeed\n");

    SetLastError(0xdeadbeef);
    ret = SetupCreateDiskSpaceListA(NULL, 0xdeadbeef, 0);
    ok(ret == NULL,
       "Expected SetupCreateDiskSpaceListA to return NULL, got %p\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       broken(GetLastError() == 0xdeadbeef), /* NT4/Win9x/Win2k */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupCreateDiskSpaceListA((void *)0xdeadbeef, 0, 0);
    ok(ret == NULL,
       "Expected SetupCreateDiskSpaceListA to return NULL, got %p\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       broken(GetLastError() == 0xdeadbeef), /* NT4/Win9x/Win2k */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());

    SetLastError(0xdeadbeef);
    ret = SetupCreateDiskSpaceListA((void *)0xdeadbeef, 0xdeadbeef, 0);
    ok(ret == NULL,
       "Expected SetupCreateDiskSpaceListA to return NULL, got %p\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER ||
       broken(GetLastError() == 0xdeadbeef), /* NT4/Win9x/Win2k */
       "Expected GetLastError() to return ERROR_INVALID_PARAMETER, got %u\n",
       GetLastError());
}