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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IInternetZoneManager ;
typedef  int /*<<< orphan*/  IInternetSecurityManager ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int IInternetSecurityManager_ProcessUrlAction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IInternetZoneManager_GetZoneActionPolicy (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int S_FALSE ; 
 int S_OK ; 
 int URLPOLICY_DISALLOW ; 
 int /*<<< orphan*/  URLZONEREG_DEFAULT ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  url1 ; 

__attribute__((used)) static void test_special_url_action(IInternetSecurityManager *secmgr, IInternetZoneManager *zonemgr, DWORD action)
{
    DWORD policy;
    HRESULT hres;

    policy = 0xdeadbeef;
    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 3, action, (BYTE*)&policy,
            sizeof(DWORD), URLZONEREG_DEFAULT);
    ok(hres == S_OK, "GetZoneActionPolicy failed: %08x\n", hres);
    ok(policy == URLPOLICY_DISALLOW, "(%x) policy=%x, expected URLPOLICY_DISALLOW\n", action, policy);

    policy = 0xdeadbeef;
    hres = IInternetSecurityManager_ProcessUrlAction(secmgr, url1, action, (BYTE*)&policy,
            sizeof(WCHAR), NULL, 0, 0, 0);
    ok(hres == S_FALSE, "ProcessUrlAction(%x) failed: %08x, expected S_FALSE\n", action, hres);

    policy = 0xdeadbeef;
    hres = IInternetSecurityManager_ProcessUrlAction(secmgr, url1, action, (BYTE*)&policy,
            sizeof(DWORD), NULL, 0, 0, 0);
    ok(hres == S_FALSE, "ProcessUrlAction(%x) failed: %08x, expected S_FALSE\n", action, hres);
    ok(policy == URLPOLICY_DISALLOW, "policy = %x\n", policy);
}