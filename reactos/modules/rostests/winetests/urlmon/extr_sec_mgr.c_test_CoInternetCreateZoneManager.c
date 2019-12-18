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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetZoneManager ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IInternetZoneManager ; 
 int /*<<< orphan*/  IID_IInternetZoneManagerEx ; 
 int /*<<< orphan*/  IID_IInternetZoneManagerEx2 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IInternetZoneManager_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CoInternetCreateZoneManager(void)
{
    IInternetZoneManager *zonemgr = NULL;
    IUnknown *punk = NULL;
    HRESULT hr;

    trace("simple zone manager tests...\n");

    hr = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hr == S_OK, "CoInternetCreateZoneManager result: 0x%x\n", hr);
    if (FAILED(hr))
        return;

    hr = IInternetZoneManager_QueryInterface(zonemgr, &IID_IUnknown, (void **) &punk);
    ok(SUCCEEDED(hr), "got 0x%x with %p (expected Success)\n", hr, punk);
    if (punk)
        IUnknown_Release(punk);

    hr = IInternetZoneManager_QueryInterface(zonemgr, &IID_IInternetZoneManager, (void **) &punk);
    ok(SUCCEEDED(hr), "got 0x%x with %p (expected Success)\n", hr, punk);
    if (punk)
        IUnknown_Release(punk);


    hr = IInternetZoneManager_QueryInterface(zonemgr, &IID_IInternetZoneManagerEx, (void **) &punk);
    if (SUCCEEDED(hr)) {
        IUnknown_Release(punk);

        hr = IInternetZoneManager_QueryInterface(zonemgr, &IID_IInternetZoneManagerEx2, (void **) &punk);
        ok(hr == S_OK || broken(hr == E_NOINTERFACE /* some W2K3 */),
           "got 0x%x (expected S_OK)\n", hr);
        if (punk)
            IUnknown_Release(punk);
        else
            win_skip("InternetZoneManagerEx2 not supported\n");

    }
    else
        win_skip("InternetZoneManagerEx not supported\n");

    hr = IInternetZoneManager_Release(zonemgr);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

}