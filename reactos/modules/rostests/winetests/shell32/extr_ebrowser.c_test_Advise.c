#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; int completed; TYPE_1__ IExplorerBrowserEvents_iface; } ;
typedef  TYPE_1__ IExplorerBrowserEvents ;
typedef  int /*<<< orphan*/  IExplorerBrowser ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int IExplorerBrowser_Advise (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int IExplorerBrowser_Destroy (int /*<<< orphan*/ *) ; 
 int IExplorerBrowser_Release (int /*<<< orphan*/ *) ; 
 int IExplorerBrowser_Unadvise (int /*<<< orphan*/ *,int) ; 
 int S_OK ; 
 TYPE_2__ ebev ; 
 int /*<<< orphan*/  ebevents ; 
 int /*<<< orphan*/  ebrowser_browse_to_desktop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebrowser_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebrowser_instantiate (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  process_msgs () ; 

__attribute__((used)) static void test_Advise(void)
{
    IExplorerBrowser *peb;
    IExplorerBrowserEvents *pebe;
    DWORD cookies[10];
    HRESULT hr;
    UINT i, ref;

    /* Set up our IExplorerBrowserEvents implementation */
    ebev.IExplorerBrowserEvents_iface.lpVtbl = &ebevents;
    pebe = &ebev.IExplorerBrowserEvents_iface;

    ebrowser_instantiate(&peb);

    if(0)
    {
        /* Crashes on Windows 7 */
        IExplorerBrowser_Advise(peb, pebe, NULL);
        IExplorerBrowser_Advise(peb, NULL, &cookies[0]);
    }

    /* Using Unadvise with a cookie that has yet to be given out
     * results in E_INVALIDARG */
    hr = IExplorerBrowser_Unadvise(peb, 11);
    ok(hr == E_INVALIDARG, "got (0x%08x)\n", hr);

    /* Add some before initialization */
    for(i = 0; i < 5; i++)
    {
        hr = IExplorerBrowser_Advise(peb, pebe, &cookies[i]);
        ok(hr == S_OK, "got (0x%08x)\n", hr);
    }

    ebrowser_initialize(peb);

    /* Add some after initialization */
    for(i = 5; i < 10; i++)
    {
        hr = IExplorerBrowser_Advise(peb, pebe, &cookies[i]);
        ok(hr == S_OK, "got (0x%08x)\n", hr);
    }

    ok(ebev.ref == 10, "Got %d\n", ebev.ref);

    ebev.completed = 0;
    ebrowser_browse_to_desktop(peb);
    process_msgs();
    ok(ebev.completed == 10, "Got %d\n", ebev.completed);

    /* Remove a bunch somewhere in the middle */
    for(i = 4; i < 8; i++)
    {
        hr = IExplorerBrowser_Unadvise(peb, cookies[i]);
        ok(hr == S_OK, "got (0x%08x)\n", hr);
    }

    ebev.completed = 0;
    ebrowser_browse_to_desktop(peb);
    process_msgs();
    ok(ebev.completed == 6, "Got %d\n", ebev.completed);

    if(0)
    {
        /* Using unadvise with a previously unadvised cookie results
         * in a crash. */
        IExplorerBrowser_Unadvise(peb, cookies[5]);
    }

    /* Remove the rest. */
    for(i = 0; i < 10; i++)
    {
        if(i<4||i>7)
        {
            hr = IExplorerBrowser_Unadvise(peb, cookies[i]);
            ok(hr == S_OK, "%d: got (0x%08x)\n", i, hr);
        }
    }

    ok(ebev.ref == 0, "Got %d\n", ebev.ref);

    ebev.completed = 0;
    ebrowser_browse_to_desktop(peb);
    process_msgs();
    ok(ebev.completed == 0, "Got %d\n", ebev.completed);

    /* ::Destroy implies ::Unadvise. */
    hr = IExplorerBrowser_Advise(peb, pebe, &cookies[0]);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(ebev.ref == 1, "Got %d\n", ebev.ref);

    hr = IExplorerBrowser_Destroy(peb);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(ebev.ref == 0, "Got %d\n", ebev.ref);

    ref = IExplorerBrowser_Release(peb);
    ok(!ref, "Got %d\n", ref);
}