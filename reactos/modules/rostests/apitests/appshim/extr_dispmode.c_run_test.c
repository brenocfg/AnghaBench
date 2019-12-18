#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ winver; int /*<<< orphan*/  dll; int /*<<< orphan*/  (* unhook ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  second; int /*<<< orphan*/  post; int /*<<< orphan*/  pre; int /*<<< orphan*/  reason; int /*<<< orphan*/  name; scalar_t__ (* hook ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetModuleHandleW (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LoadShimDLL (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ _WIN32_WINNT_WS03 ; 
 scalar_t__ g_Version ; 
 scalar_t__ get_module_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * pGetHookAPIs ; 
 void* pNotifyShims ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tests ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_test(size_t n, BOOL unload)
{
    BOOL ret;
    HMODULE dll;

    if (!LoadShimDLL(tests[n].dll, &dll, &pGetHookAPIs))
        pGetHookAPIs = NULL;
    pNotifyShims = (void*)GetProcAddress(dll, "NotifyShims");

    if (!pGetHookAPIs || !pNotifyShims)
    {
        skip("%s not loaded, or does not export GetHookAPIs or pNotifyShims (%s, %p, %p)\n",
             wine_dbgstr_w(tests[n].dll), tests[n].name, pGetHookAPIs, pNotifyShims);
        return;
    }

    g_Version = get_module_version(dll);

    if (!g_Version)
    {
        g_Version = _WIN32_WINNT_WS03;
        trace("Module %s has no version, faking 2k3\n", wine_dbgstr_w(tests[n].dll));
    }

    if (g_Version >= tests[n].winver)
    {
        ret = tests[n].hook(dll);
        if (ret)
        {
            test_one(tests[n].name, tests[n].reason, tests[n].pre, tests[n].post, tests[n].second);
            tests[n].unhook(dll);
        }
        else
        {
            ok(0, "Unable to redirect functions!\n");
        }
    }
    FreeLibrary(dll);
    if (unload)
    {
        dll = GetModuleHandleW(tests[n].dll);
        ok(dll == NULL, "Unable to unload %s\n", wine_dbgstr_w(tests[n].dll));
    }
}