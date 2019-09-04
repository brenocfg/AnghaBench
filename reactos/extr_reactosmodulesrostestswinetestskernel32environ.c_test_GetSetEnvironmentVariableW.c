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
typedef  char WCHAR ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_ENVVAR_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetEnvironmentVariableW (char const*,char*,scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ SetEnvironmentVariableW (char const*,char const*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 scalar_t__ lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_w (int,char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSetEnvironmentVariableW(void)
{
    WCHAR buf[256];
    BOOL ret;
    DWORD ret_size;
    static const WCHAR name[] = {'S','o','m','e','W','i','l','d','N','a','m','e',0};
    static const WCHAR value[] = {'S','o','m','e','W','i','l','d','V','a','l','u','e',0};
    static const WCHAR name_cased[] = {'s','O','M','E','w','I','L','D','n','A','M','E',0};
    static const WCHAR empty_strW[] = { 0 };
    static const WCHAR fooW[] = {'f','o','o',0};

    ret = SetEnvironmentVariableW(name, value);
    if (ret == FALSE && GetLastError()==ERROR_CALL_NOT_IMPLEMENTED)
    {
        /* Must be Win9x which doesn't support the Unicode functions */
        win_skip("SetEnvironmentVariableW is not implemented\n");
        return;
    }
    ok(ret == TRUE,
       "unexpected error in SetEnvironmentVariableW, GetLastError=%d\n",
       GetLastError());

    /* Try to retrieve the environment variable we just set */
    ret_size = GetEnvironmentVariableW(name, NULL, 0);
    ok(ret_size == lstrlenW(value) + 1,
       "should return length with terminating 0 ret_size=%d\n",
       ret_size);

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name, buf, lstrlenW(value));
    ok_w(lstrcmpW(buf, fooW) == 0 ||
         lstrlenW(buf) == 0, /* Vista */
         "Expected untouched or empty buffer, got \"%s\"\n", buf);

    ok(ret_size == lstrlenW(value) + 1,
       "should return length with terminating 0 ret_size=%d\n", ret_size);

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name, buf, lstrlenW(value) + 1);
    ok(lstrcmpW(buf, value) == 0, "should touch the buffer\n");
    ok(ret_size == lstrlenW(value),
       "should return length without terminating 0 ret_size=%d\n", ret_size);

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name_cased, buf, lstrlenW(value) + 1);
    ok(lstrcmpW(buf, value) == 0, "should touch the buffer\n");
    ok(ret_size == lstrlenW(value),
       "should return length without terminating 0 ret_size=%d\n", ret_size);

    /* Remove that environment variable */
    ret = SetEnvironmentVariableW(name_cased, NULL);
    ok(ret == TRUE, "should erase existing variable\n");

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name, buf, lstrlenW(value) + 1);
    ok(lstrcmpW(buf, fooW) == 0, "should not touch the buffer\n");
    ok(ret_size == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND,
       "should not find variable but ret_size=%d GetLastError=%d\n",
       ret_size, GetLastError());

    /* Check behavior of SetEnvironmentVariableW(name, "") */
    ret = SetEnvironmentVariableW(name, value);
    ok(ret == TRUE,
       "unexpected error in SetEnvironmentVariableW, GetLastError=%d\n",
       GetLastError());

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name, buf, lstrlenW(value) + 1);
    ok(lstrcmpW(buf, value) == 0, "should touch the buffer\n");
    ok(ret_size == lstrlenW(value),
       "should return length without terminating 0 ret_size=%d\n", ret_size);

    ret = SetEnvironmentVariableW(name_cased, empty_strW);
    ok(ret == TRUE, "should not fail with empty value but GetLastError=%d\n", GetLastError());

    lstrcpyW(buf, fooW);
    ret_size = GetEnvironmentVariableW(name, buf, lstrlenW(value) + 1);
    ok(ret_size == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND,
       "should not find variable but ret_size=%d GetLastError=%d\n",
       ret_size, GetLastError());
    ok(lstrcmpW(buf, empty_strW) == 0, "should copy an empty string\n");

    /* Test the limits */
    ret_size = GetEnvironmentVariableW(NULL, NULL, 0);
    ok(ret_size == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND,
       "should not find variable but ret_size=%d GetLastError=%d\n",
       ret_size, GetLastError());

    if (0) /* Both tests crash on Vista */
    {
        ret_size = GetEnvironmentVariableW(NULL, buf, lstrlenW(value) + 1);
        ok(ret_size == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND,
           "should not find variable but ret_size=%d GetLastError=%d\n",
           ret_size, GetLastError());

        ret = SetEnvironmentVariableW(NULL, NULL);
        ok(ret == FALSE && (GetLastError() == ERROR_INVALID_PARAMETER || GetLastError() == ERROR_ENVVAR_NOT_FOUND),
           "should fail with NULL, NULL but ret=%d and GetLastError=%d\n",
           ret, GetLastError());
    }
}