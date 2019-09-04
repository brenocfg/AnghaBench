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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (char const*) ; 
 scalar_t__ ITask_GetComment (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ ITask_SetComment (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  cleanup_task () ; 
 char const* empty ; 
 int /*<<< orphan*/  lstrcmpW (char const*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setup_task () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task ; 
 scalar_t__ wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_SetComment_GetComment(void)
{
    BOOL setup;
    HRESULT hres;
    LPWSTR comment;
    const WCHAR comment_a[] = {'C','o','m','m','e','n','t','.', 0};
    const WCHAR comment_b[] = {'L','o','n','g','e','r',' ',
            'c','o','m','m','e','n','t','.', 0};

    setup = setup_task();
    ok(setup, "Failed to setup test_task\n");
    if (!setup)
    {
        skip("Failed to create task.  Skipping tests.\n");
        return;
    }

    /* Get comment before setting it*/
    hres = ITask_GetComment(test_task, &comment);
    ok(hres == S_OK, "GetComment failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(comment, empty),
                "Got %s, expected empty string\n", wine_dbgstr_w(comment));
        CoTaskMemFree(comment);
    }

    /* Set comment to a simple string */
    hres = ITask_SetComment(test_task, comment_a);
    ok(hres == S_OK, "Failed setting comment %s: %08x\n",
            wine_dbgstr_w(comment_a), hres);
    hres = ITask_GetComment(test_task, &comment);
    ok(hres == S_OK, "GetComment failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(comment, comment_a), "Got %s, expected %s\n",
                wine_dbgstr_w(comment), wine_dbgstr_w(comment_a));
        CoTaskMemFree(comment);
    }

    /* Update comment to a different simple string */
    hres = ITask_SetComment(test_task, comment_b);
    ok(hres == S_OK, "Failed setting comment %s: %08x\n",
            wine_dbgstr_w(comment_b), hres);
    hres = ITask_GetComment(test_task, &comment);
    ok(hres == S_OK, "GetComment failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(comment, comment_b), "Got %s, expected %s\n",
                wine_dbgstr_w(comment), wine_dbgstr_w(comment_b));
        CoTaskMemFree(comment);
    }

    /* Clear comment */
    hres = ITask_SetComment(test_task, empty);
    ok(hres == S_OK, "Failed setting comment %s: %08x\n",
            wine_dbgstr_w(empty), hres);
    hres = ITask_GetComment(test_task, &comment);
    ok(hres == S_OK, "GetComment failed: %08x\n", hres);
    if (hres == S_OK)
    {
        ok(!lstrcmpW(comment, empty),
                "Got %s, expected empty string\n", wine_dbgstr_w(comment));
        CoTaskMemFree(comment);
    }

    cleanup_task();
    return;
}