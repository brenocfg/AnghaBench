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

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char*) ; 
 scalar_t__ DsMakeSpnW (char const*,char const*,char const*,int,char const*,scalar_t__*,char*) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 scalar_t__ lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_DsMakeSpn(void)
{
    DWORD ret;
    WCHAR spn[256];
    DWORD spn_length;
    static const WCHAR wszServiceClass[] = {'c','l','a','s','s',0};
    static const WCHAR wszServiceHost[] = {'h','o','s','t',0};
    static const WCHAR wszInstanceName[] = {'i','n','s','t','a','n','c','e',0};
    static const WCHAR wszReferrer[] = {'r','e','f','e','r','r','e','r',0};
    static const WCHAR wszSpn1[] = {'c','l','a','s','s','/','h','o','s','t',0};
    static const WCHAR wszSpn2[] = {'c','l','a','s','s','/','i','n','s','t','a','n','c','e','/','h','o','s','t',0};
    static const WCHAR wszSpn3[] = {'c','l','a','s','s','/','i','n','s','t','a','n','c','e',':','5','5','5','/','h','o','s','t',0};
    static const WCHAR wszSpn4[] = {'c','l','a','s','s','/','i','n','s','t','a','n','c','e',':','5','5','5','/','h','o','s','t',0};
    static const WCHAR wszSpn5[] = {'c','l','a','s','s','/','h','o','s','t',':','5','5','5',0};

    spn[0] = '\0';

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(NULL, NULL, NULL, 0, NULL, &spn_length, spn);
    ok(ret == ERROR_INVALID_PARAMETER, "DsMakeSpnW should have failed with ERROR_INVALID_PARAMETER instead of %d\n", ret);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(NULL, wszServiceHost, NULL, 0, NULL, &spn_length, spn);
    ok(ret == ERROR_INVALID_PARAMETER, "DsMakeSpnW should have failed with ERROR_INVALID_PARAMETER instead of %d\n", ret);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(wszServiceClass, wszServiceHost, NULL, 0, NULL, &spn_length, spn);
    ok(ret == ERROR_SUCCESS, "DsMakeSpnW should have succeeded instead of failing with %d\n", ret);
    ok(!lstrcmpW(spn, wszSpn1), "DsMakeSpnW returned unexpected SPN %s\n", wine_dbgstr_w(spn));
    ok(spn_length == lstrlenW(wszSpn1) + 1, "DsMakeSpnW should have returned spn_length of %d instead of %d\n", lstrlenW(wszSpn1) + 1, spn_length);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(wszServiceClass, wszServiceHost, wszInstanceName, 0, NULL, &spn_length, spn);
    ok(ret == ERROR_SUCCESS, "DsMakeSpnW should have succeeded instead of failing with %d\n", ret);
    ok(!lstrcmpW(spn, wszSpn2), "DsMakeSpnW returned unexpected SPN %s\n", wine_dbgstr_w(spn));
    ok(spn_length == lstrlenW(wszSpn2) + 1, "DsMakeSpnW should have returned spn_length of %d instead of %d\n", lstrlenW(wszSpn2) + 1, spn_length);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(wszServiceClass, wszServiceHost, wszInstanceName, 555, NULL, &spn_length, spn);
    ok(ret == ERROR_SUCCESS, "DsMakeSpnW should have succeeded instead of failing with %d\n", ret);
    ok(!lstrcmpW(spn, wszSpn3), "DsMakeSpnW returned unexpected SPN %s\n", wine_dbgstr_w(spn));
    ok(spn_length == lstrlenW(wszSpn3) + 1, "DsMakeSpnW should have returned spn_length of %d instead of %d\n", lstrlenW(wszSpn3) + 1, spn_length);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(wszServiceClass, wszServiceHost, wszInstanceName, 555, wszReferrer, &spn_length, spn);
    ok(ret == ERROR_SUCCESS, "DsMakeSpnW should have succeeded instead of failing with %d\n", ret);
    ok(!lstrcmpW(spn, wszSpn4), "DsMakeSpnW returned unexpected SPN %s\n", wine_dbgstr_w(spn));
    ok(spn_length == lstrlenW(wszSpn4) + 1, "DsMakeSpnW should have returned spn_length of %d instead of %d\n", lstrlenW(wszSpn4) + 1, spn_length);

    spn_length = ARRAY_SIZE(spn);
    ret = DsMakeSpnW(wszServiceClass, wszServiceHost, NULL, 555, wszReferrer, &spn_length, spn);
    ok(ret == ERROR_SUCCESS, "DsMakeSpnW should have succeeded instead of failing with %d\n", ret);
    ok(!lstrcmpW(spn, wszSpn5), "DsMakeSpnW returned unexpected SPN %s\n", wine_dbgstr_w(spn));
    ok(spn_length == lstrlenW(wszSpn5) + 1, "DsMakeSpnW should have returned spn_length of %d instead of %d\n", lstrlenW(wszSpn5) + 1, spn_length);
}