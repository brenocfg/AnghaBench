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
typedef  int /*<<< orphan*/  IInternetZoneManager ;
typedef  int /*<<< orphan*/  IInternetSecurityManager ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IInternetSecurityManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int URLACTION_ACTIVEX_OVERRIDE_OBJECT_SAFETY ; 
 int /*<<< orphan*/  URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY ; 
 int URLACTION_ACTIVEX_RUN ; 
 int URLACTION_CHANNEL_SOFTDIST_PERMISSIONS ; 
 int /*<<< orphan*/  URLACTION_SCRIPT_OVERRIDE_SAFETY ; 
 int URLACTION_SCRIPT_RUN ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInternetCreateSecurityManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_activex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_special_url_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_url_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_polices(void)
{
    IInternetZoneManager *zonemgr = NULL;
    IInternetSecurityManager *secmgr = NULL;
    HRESULT hres;

    trace("testing polices...\n");

    hres = pCoInternetCreateSecurityManager(NULL, &secmgr, 0);
    ok(hres == S_OK, "CoInternetCreateSecurityManager failed: %08x\n", hres);
    hres = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hres == S_OK, "CoInternetCreateZoneManager failed: %08x\n", hres);

    test_url_action(secmgr, zonemgr, URLACTION_SCRIPT_RUN);
    test_url_action(secmgr, zonemgr, URLACTION_ACTIVEX_RUN);
    test_url_action(secmgr, zonemgr, URLACTION_ACTIVEX_OVERRIDE_OBJECT_SAFETY);
    test_url_action(secmgr, zonemgr, URLACTION_CHANNEL_SOFTDIST_PERMISSIONS);
    test_url_action(secmgr, zonemgr, 0xdeadbeef);

    test_special_url_action(secmgr, zonemgr, URLACTION_SCRIPT_OVERRIDE_SAFETY);
    test_special_url_action(secmgr, zonemgr, URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY);

    test_activex(secmgr);

    IInternetSecurityManager_Release(secmgr);
    IInternetZoneManager_Release(zonemgr);
}