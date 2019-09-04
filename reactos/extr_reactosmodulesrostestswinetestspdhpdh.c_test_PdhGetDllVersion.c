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
typedef  scalar_t__ PDH_STATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ PDH_CVERSION_WIN50 ; 
 scalar_t__ PDH_INVALID_ARGUMENT ; 
 scalar_t__ PDH_VERSION ; 
 scalar_t__ PdhGetDllVersion (scalar_t__*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_PdhGetDllVersion(void)
{
    PDH_STATUS ret;
    DWORD version;

    ret = PdhGetDllVersion(NULL);
    ok(ret == PDH_INVALID_ARGUMENT ||
       broken(ret == ERROR_SUCCESS), /* Vista+ */
       "Expected PdhGetDllVersion to return PDH_INVALID_ARGUMENT, got %d\n", ret);

    ret = PdhGetDllVersion(&version);
    ok(ret == ERROR_SUCCESS,
       "Expected PdhGetDllVersion to return ERROR_SUCCESS, got %d\n", ret);

    if (ret == ERROR_SUCCESS)
    {
        ok(version == PDH_CVERSION_WIN50 ||
           version == PDH_VERSION,
           "Expected version number to be PDH_CVERSION_WIN50 or PDH_VERSION, got %u\n", version);
    }
}