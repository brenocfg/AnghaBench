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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION ; 
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION ; 
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_manifest (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kernel32_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntdll_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pActivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testdep_manifest3 ; 

__attribute__((used)) static void test_findsectionstring(void)
{
    HANDLE handle;
    BOOL ret;
    ULONG_PTR cookie;

    handle = create_manifest("test.manifest", testdep_manifest3, __LINE__);
    ret = pActivateActCtx(handle, &cookie);
    ok(ret, "ActivateActCtx failed: %u\n", GetLastError());

    /* first we show the parameter validation from kernel32 */
    kernel32_find(ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION, "testdep", FALSE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib.dll", TRUE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib2.dll", TRUE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib3.dll", FALSE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass", TRUE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass2", TRUE, __LINE__);
    kernel32_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass3", FALSE, __LINE__);

    /* then we show that ntdll plays by different rules */
    ntdll_find(ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION, "testdep", FALSE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib.dll", TRUE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib2.dll", TRUE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION, "testlib3.dll", FALSE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass", TRUE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass2", TRUE, __LINE__);
    ntdll_find(ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION, "wndClass3", FALSE, __LINE__);

    ret = pDeactivateActCtx(0, cookie);
    ok(ret, "DeactivateActCtx failed: %u\n", GetLastError());
    pReleaseActCtx(handle);
}