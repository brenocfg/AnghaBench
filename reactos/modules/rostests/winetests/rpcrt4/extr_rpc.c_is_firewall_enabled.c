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
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  INetFwProfile ;
typedef  int /*<<< orphan*/  INetFwPolicy ;
typedef  int /*<<< orphan*/  INetFwMgr ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NetFwMgr ; 
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CoInitializeEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IID_INetFwMgr ; 
 int /*<<< orphan*/  INetFwMgr_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwMgr_get_LocalPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwPolicy_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwPolicy_get_CurrentProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwProfile_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwProfile_get_FirewallEnabled (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VARIANT_FALSE ; 
 scalar_t__ VARIANT_TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static BOOL is_firewall_enabled(void)
{
    HRESULT hr, init;
    INetFwMgr *mgr = NULL;
    INetFwPolicy *policy = NULL;
    INetFwProfile *profile = NULL;
    VARIANT_BOOL enabled = VARIANT_FALSE;

    init = CoInitializeEx( 0, COINIT_APARTMENTTHREADED );

    hr = CoCreateInstance( &CLSID_NetFwMgr, NULL, CLSCTX_INPROC_SERVER, &IID_INetFwMgr,
                           (void **)&mgr );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = INetFwMgr_get_LocalPolicy( mgr, &policy );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = INetFwPolicy_get_CurrentProfile( policy, &profile );
    if (hr != S_OK) goto done;

    hr = INetFwProfile_get_FirewallEnabled( profile, &enabled );
    ok( hr == S_OK, "got %08x\n", hr );

done:
    if (policy) INetFwPolicy_Release( policy );
    if (profile) INetFwProfile_Release( profile );
    if (mgr) INetFwMgr_Release( mgr );
    if (SUCCEEDED( init )) CoUninitialize();
    return (enabled == VARIANT_TRUE);
}