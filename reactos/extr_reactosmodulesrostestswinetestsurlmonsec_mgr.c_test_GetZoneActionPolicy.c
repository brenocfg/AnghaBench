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
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_FOUND ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IInternetZoneManager_GetZoneActionPolicy (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ URLACTION_CREDENTIALS_USE ; 
 scalar_t__ URLPOLICY_CREDENTIALS_ANONYMOUS_ONLY ; 
 scalar_t__ URLPOLICY_CREDENTIALS_CONDITIONAL_PROMPT ; 
 scalar_t__ URLPOLICY_CREDENTIALS_MUST_PROMPT_USER ; 
 scalar_t__ URLPOLICY_CREDENTIALS_SILENT_LOGON_OK ; 
 int /*<<< orphan*/  URLZONEREG_DEFAULT ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_GetZoneActionPolicy(void)
{
    IInternetZoneManager *zonemgr = NULL;
    BYTE buf[32];
    HRESULT hres;
    DWORD action = URLACTION_CREDENTIALS_USE; /* Implemented on all IE versions */

    trace("testing GetZoneActionPolixy...\n");

    hres = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hres == S_OK, "CoInternetCreateZoneManager failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 3, action, buf,
            sizeof(DWORD), URLZONEREG_DEFAULT);
    ok(hres == S_OK, "GetZoneActionPolicy failed: %08x\n", hres);
    ok(*(DWORD*)buf == URLPOLICY_CREDENTIALS_SILENT_LOGON_OK ||
            *(DWORD*)buf == URLPOLICY_CREDENTIALS_MUST_PROMPT_USER ||
            *(DWORD*)buf == URLPOLICY_CREDENTIALS_CONDITIONAL_PROMPT ||
            *(DWORD*)buf == URLPOLICY_CREDENTIALS_ANONYMOUS_ONLY,
            "unexpected policy=%d\n", *(DWORD*)buf);

    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 3, action, NULL,
            sizeof(DWORD), URLZONEREG_DEFAULT);
    ok(hres == E_INVALIDARG, "GetZoneActionPolicy failed: %08x, expected E_INVALIDARG\n", hres);

    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 3, action, buf,
            2, URLZONEREG_DEFAULT);
    ok(hres == E_INVALIDARG, "GetZoneActionPolicy failed: %08x, expected E_INVALIDARG\n", hres);

    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 3, 0x1fff, buf,
            sizeof(DWORD), URLZONEREG_DEFAULT);
    ok(hres == E_FAIL || broken(hres == HRESULT_FROM_WIN32(ERROR_NOT_FOUND)),
            "(0x%x) got 0x%x (expected E_FAIL)\n", action, hres);

    hres = IInternetZoneManager_GetZoneActionPolicy(zonemgr, 13, action, buf,
            sizeof(DWORD), URLZONEREG_DEFAULT);
    ok(hres == E_INVALIDARG, "GetZoneActionPolicy failed: %08x, expected E_INVALIDARG\n", hres);

    IInternetZoneManager_Release(zonemgr);
}