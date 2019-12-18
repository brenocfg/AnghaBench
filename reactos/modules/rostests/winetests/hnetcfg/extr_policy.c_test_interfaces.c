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
typedef  int /*<<< orphan*/  INetFwPolicy2 ;
typedef  int /*<<< orphan*/  INetFwPolicy ;
typedef  int /*<<< orphan*/  INetFwMgr ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NetFwMgr ; 
 int /*<<< orphan*/  CLSID_NetFwPolicy2 ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_INetFwMgr ; 
 int /*<<< orphan*/  IID_INetFwPolicy ; 
 int /*<<< orphan*/  IID_INetFwPolicy2 ; 
 scalar_t__ INetFwMgr_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  INetFwMgr_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwMgr_get_LocalPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwPolicy2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwPolicy_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  INetFwPolicy_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_policy2_rules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*,scalar_t__) ; 

__attribute__((used)) static void test_interfaces(void)
{
    INetFwMgr *manager;
    INetFwPolicy *policy;
    INetFwPolicy2 *policy2;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_NetFwMgr, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_INetFwMgr, (void**)&manager);
    ok(hr == S_OK, "NetFwMgr create failed: %08x\n", hr);

    hr = INetFwMgr_QueryInterface(manager, &IID_INetFwPolicy, (void**)&policy);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    hr = INetFwMgr_QueryInterface(manager, &IID_INetFwPolicy2, (void**)&policy2);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    hr = INetFwMgr_get_LocalPolicy(manager, &policy);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = INetFwPolicy_QueryInterface(policy, &IID_INetFwPolicy2, (void**)&policy2);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    INetFwPolicy_Release(policy);

    hr = CoCreateInstance(&CLSID_NetFwPolicy2, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_INetFwPolicy2, (void**)&policy2);
    if(hr == S_OK)
    {
        test_policy2_rules(policy2);

        INetFwPolicy2_Release(policy2);
    }
    else
        win_skip("NetFwPolicy2 object is not supported: %08x\n", hr);

    INetFwMgr_Release(manager);
}