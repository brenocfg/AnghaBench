#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cmd; } ;
typedef  TYPE_1__ cmdline_tests_t ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 char** CommandLineToArgvW (char const*,int*) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (char**) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* cmdline_tests ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_one_cmdline (TYPE_1__ const*) ; 
 char** wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_commandline2argv(void)
{
    static const WCHAR exeW[] = {'e','x','e',0};
    const cmdline_tests_t* test;
    WCHAR strW[MAX_PATH];
    LPWSTR *args;
    int numargs;
    DWORD le;

    test = cmdline_tests;
    while (test->cmd)
    {
        if (!test_one_cmdline(test))
            return;
        test++;
    }

    SetLastError(0xdeadbeef);
    args = CommandLineToArgvW(exeW, NULL);
    le = GetLastError();
    ok(args == NULL && le == ERROR_INVALID_PARAMETER, "expected NULL with ERROR_INVALID_PARAMETER got %p with %u\n", args, le);

    SetLastError(0xdeadbeef);
    args = CommandLineToArgvW(NULL, NULL);
    le = GetLastError();
    ok(args == NULL && le == ERROR_INVALID_PARAMETER, "expected NULL with ERROR_INVALID_PARAMETER got %p with %u\n", args, le);

    *strW = 0;
    args = CommandLineToArgvW(strW, &numargs);
    ok(numargs == 1 || broken(numargs > 1), "expected 1 args, got %d\n", numargs);
    ok(!args || (!args[numargs] || broken(args[numargs] != NULL) /* before Vista */),
       "expected NULL-terminated list of commandline arguments\n");
    if (numargs == 1)
    {
        GetModuleFileNameW(NULL, strW, ARRAY_SIZE(strW));
        ok(!lstrcmpW(args[0], strW), "wrong path to the current executable: %s instead of %s\n", wine_dbgstr_w(args[0]), wine_dbgstr_w(strW));
    }
    if (args) LocalFree(args);
}