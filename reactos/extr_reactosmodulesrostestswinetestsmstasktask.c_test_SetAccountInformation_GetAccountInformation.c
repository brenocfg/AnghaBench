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
typedef  char const* LPWSTR ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (char const*) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int ITask_GetAccountInformation (int /*<<< orphan*/ ,char const**) ; 
 int ITask_SetAccountInformation (int /*<<< orphan*/ ,char const*,char const*) ; 
 int SCHED_E_CANNOT_OPEN_TASK ; 
 int SCHED_E_NO_SECURITY_SERVICES ; 
 int SCHED_E_SERVICE_NOT_RUNNING ; 
 int S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  cleanup_task () ; 
 char const* empty ; 
 int /*<<< orphan*/  lstrcmpW (char const*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setup_task () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_SetAccountInformation_GetAccountInformation(void)
{
    BOOL setup;
    HRESULT hres;
    LPWSTR account_name;
    const WCHAR dummy_account_name[] = {'N', 'o', 'S', 'u', 'c', 'h',
            'A', 'c', 'c', 'o', 'u', 'n', 't', 0};
    const WCHAR dummy_account_name_b[] = {'N', 'o', 'S', 'u', 'c', 'h',
            'A', 'c', 'c', 'o', 'u', 'n', 't', 'B', 0};

    setup = setup_task();
    ok(setup, "Failed to setup test_task\n");
    if (!setup)
    {
        skip("Failed to create task.  Skipping tests.\n");
        return;
    }

    /* Get account information before it is set */
    hres = ITask_GetAccountInformation(test_task, &account_name);
    /* WinXP returns HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND): 0x80070002 but
     * Win2K returns SCHED_E_CANNOT_OPEN_TASK: 0x8004130d
     * Win9x doesn't support security services */
    if (hres == SCHED_E_NO_SECURITY_SERVICES || hres == SCHED_E_SERVICE_NOT_RUNNING)
    {
        win_skip("Security services are not supported\n");
        cleanup_task();
        return;
    }
    ok(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
            hres == SCHED_E_CANNOT_OPEN_TASK,
            "Unset account name generated: 0x%08x\n", hres);

    /* Attempt to set to a dummy account without a password */
    /* This test passes on WinXP but fails on Win2K */
    hres = ITask_SetAccountInformation(test_task, dummy_account_name, NULL);
    ok(hres == S_OK,
            "Failed setting dummy account with no password: %08x\n", hres);
    hres = ITask_GetAccountInformation(test_task, &account_name);
    ok(hres == S_OK ||
       broken(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
              hres == SCHED_E_CANNOT_OPEN_TASK ||
              hres == 0x200),  /* win2k */
       "GetAccountInformation failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(account_name, dummy_account_name),
                "Got %s, expected %s\n", wine_dbgstr_w(account_name),
                wine_dbgstr_w(dummy_account_name));
        CoTaskMemFree(account_name);
    }

    /* Attempt to set to a dummy account with a (invalid) password */
    /* This test passes on WinXP but fails on Win2K */
    hres = ITask_SetAccountInformation(test_task, dummy_account_name_b,
            dummy_account_name_b);
    ok(hres == S_OK,
            "Failed setting dummy account with password: %08x\n", hres);
    hres = ITask_GetAccountInformation(test_task, &account_name);
    ok(hres == S_OK ||
       broken(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
              hres == SCHED_E_CANNOT_OPEN_TASK ||
              hres == 0x200),  /* win2k */
       "GetAccountInformation failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(account_name, dummy_account_name_b),
                "Got %s, expected %s\n", wine_dbgstr_w(account_name),
                wine_dbgstr_w(dummy_account_name_b));
        CoTaskMemFree(account_name);
    }

    /* Attempt to set to the local system account */
    hres = ITask_SetAccountInformation(test_task, empty, NULL);
    ok(hres == S_OK, "Failed setting system account: %08x\n", hres);
    hres = ITask_GetAccountInformation(test_task, &account_name);
    ok(hres == S_OK ||
       broken(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
              hres == SCHED_E_CANNOT_OPEN_TASK ||
              hres == 0x200),  /* win2k */
       "GetAccountInformation failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(account_name, empty),
                "Got %s, expected empty string\n", wine_dbgstr_w(account_name));
        CoTaskMemFree(account_name);
    }

    cleanup_task();
    return;
}