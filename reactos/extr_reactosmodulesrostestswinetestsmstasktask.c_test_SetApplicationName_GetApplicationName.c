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
typedef  char const* LPCWSTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (char const*) ; 
 scalar_t__ ITask_GetApplicationName (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ ITask_SetApplicationName (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  cleanup_task () ; 
 char const* empty ; 
 scalar_t__ lstrcmpiW (char const*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* path_resolve_name (char const*) ; 
 int /*<<< orphan*/  setup_task () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task ; 
 scalar_t__ wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_SetApplicationName_GetApplicationName(void)
{
    BOOL setup;
    HRESULT hres;
    LPWSTR stored_name;
    LPCWSTR full_name;
    const WCHAR non_application_name[] = {'N','o','S','u','c','h',
            'A','p','p','l','i','c','a','t','i','o','n', 0};
    const WCHAR notepad_exe[] = {
            'n','o','t','e','p','a','d','.','e','x','e', 0};
    const WCHAR notepad[] = {'n','o','t','e','p','a','d', 0};

    setup = setup_task();
    ok(setup, "Failed to setup test_task\n");
    if (!setup)
    {
        skip("Failed to create task.  Skipping tests.\n");
        return;
    }

    /* Attempt getting before setting application name */
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpiW(stored_name, empty),
                "Got %s, expected empty string\n", wine_dbgstr_w(stored_name));
        CoTaskMemFree(stored_name);
    }

    /* Set application name to a nonexistent application and then get
     * the application name that is actually stored */
    hres = ITask_SetApplicationName(test_task, non_application_name);
    ok(hres == S_OK, "Failed setting name %s: %08x\n",
            wine_dbgstr_w(non_application_name), hres);
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        full_name = path_resolve_name(non_application_name);
        ok(!lstrcmpiW(stored_name, full_name), "Got %s, expected %s\n",
                wine_dbgstr_w(stored_name), wine_dbgstr_w(full_name));
        CoTaskMemFree(stored_name);
    }

    /* Set a valid application name with program type extension and then
     * get the stored name */
    hres = ITask_SetApplicationName(test_task, notepad_exe);
    ok(hres == S_OK, "Failed setting name %s: %08x\n",
            wine_dbgstr_w(notepad_exe), hres);
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        full_name = path_resolve_name(notepad_exe);
        ok(!lstrcmpiW(stored_name, full_name), "Got %s, expected %s\n",
                wine_dbgstr_w(stored_name), wine_dbgstr_w(full_name));
        CoTaskMemFree(stored_name);
    }

    /* Set a valid application name without program type extension and
     * then get the stored name */
    hres = ITask_SetApplicationName(test_task, notepad);
    ok(hres == S_OK, "Failed setting name %s: %08x\n", wine_dbgstr_w(notepad), hres);
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        full_name = path_resolve_name(notepad_exe);  /* XP SP1 appends .exe */
        if (lstrcmpiW(stored_name, full_name) != 0)
        {
            full_name = path_resolve_name(notepad);
            ok(!lstrcmpiW(stored_name, full_name), "Got %s, expected %s\n",
               wine_dbgstr_w(stored_name), wine_dbgstr_w(full_name));
        }
        CoTaskMemFree(stored_name);
    }

    /* After having a valid application name set, set application the name
     * to a nonexistent application and then get the name that is
     * actually stored */
    hres = ITask_SetApplicationName(test_task, non_application_name);
    ok(hres == S_OK, "Failed setting name %s: %08x\n",
            wine_dbgstr_w(non_application_name), hres);
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        full_name = path_resolve_name(non_application_name);
        ok(!lstrcmpiW(stored_name, full_name), "Got %s, expected %s\n",
                wine_dbgstr_w(stored_name), wine_dbgstr_w(full_name));
        CoTaskMemFree(stored_name);
    }

    /* Clear application name */
    hres = ITask_SetApplicationName(test_task, empty);
    ok(hres == S_OK, "Failed setting name %s: %08x\n", wine_dbgstr_w(empty), hres);
    hres = ITask_GetApplicationName(test_task, &stored_name);
    ok(hres == S_OK, "GetApplicationName failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpiW(stored_name, empty),
                "Got %s, expected empty string\n", wine_dbgstr_w(stored_name));
        CoTaskMemFree(stored_name);
    }

    cleanup_task();
    return;
}