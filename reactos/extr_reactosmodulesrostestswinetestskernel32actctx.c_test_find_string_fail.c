#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int member_0; int cbSize; } ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_1__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SXS_KEY_NOT_FOUND ; 
 scalar_t__ ERROR_SXS_SECTION_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFindActCtxSectionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * testlib2_dll ; 
 int /*<<< orphan*/ * testlib_dll ; 

__attribute__((used)) static void test_find_string_fail(void)
{
    ACTCTX_SECTION_KEYED_DATA data = {sizeof(data)};
    BOOL ret;

    ret = pFindActCtxSectionStringW(0, NULL, 100, testlib_dll, &data);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_SXS_SECTION_NOT_FOUND, "GetLastError()=%u\n", GetLastError());

    ret = pFindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib2_dll, &data);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_SXS_KEY_NOT_FOUND, "GetLastError()=%u\n", GetLastError());

    ret = pFindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib_dll, NULL);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError()=%u\n", GetLastError());

    ret = pFindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    NULL, &data);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError()=%u\n", GetLastError());

    data.cbSize = 0;
    ret = pFindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib_dll, &data);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError()=%u\n", GetLastError());

    data.cbSize = 35;
    ret = pFindActCtxSectionStringW(0, NULL, ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                    testlib_dll, &data);
    ok(!ret, "FindActCtxSectionStringW succeeded\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError()=%u\n", GetLastError());
}