#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {int cbSize; } ;
typedef  TYPE_1__ ZONEATTRIBUTES ;
typedef  int /*<<< orphan*/  IInternetZoneManager ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ IInternetZoneManager_GetZoneAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetZoneManager_SetZoneAttributes (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int URLZONE_CUSTOM ; 
 int /*<<< orphan*/  URLZONE_LOCAL_MACHINE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  myRegDeleteTreeA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 char* szInternetSettingsKey ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetZoneAttributes(void)
{
    IInternetZoneManager *zonemgr = NULL;
    CHAR buffer [sizeof(ZONEATTRIBUTES) + 16];
    ZONEATTRIBUTES* pZA = (ZONEATTRIBUTES*) buffer;
    CHAR regpath[MAX_PATH];
    HKEY hkey;
    HRESULT hr;
    DWORD res;

    trace("testing SetZoneAttributes...\n");
    hr = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hr == S_OK, "CoInternetCreateZoneManager result: 0x%x\n", hr);
    if (FAILED(hr))
        return;

    memset(buffer, -1, sizeof(buffer));
    hr = IInternetZoneManager_GetZoneAttributes(zonemgr, URLZONE_LOCAL_MACHINE, pZA);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    sprintf(regpath, "%s\\Zones\\%d", szInternetSettingsKey, URLZONE_CUSTOM);
    res = RegCreateKeyA(HKEY_CURRENT_USER, regpath, &hkey);
    RegCloseKey(hkey);

    ok(res == ERROR_SUCCESS, "got %d (expected ERROR_SUCCESS)\n", res);
    if (res != ERROR_SUCCESS)
        goto cleanup;

    pZA->cbSize = sizeof(ZONEATTRIBUTES);
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, NULL);
    ok(hr == E_INVALIDARG, "got 0x%x (expected E_INVALIDARG)\n", hr);

    /* normal use */
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, pZA);
    if (hr == E_FAIL) {
        win_skip("SetZoneAttributes not supported: IE too old\n");
        goto cleanup;
    }
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    /* native urlmon ignores cbSize */
    pZA->cbSize = sizeof(ZONEATTRIBUTES) + sizeof(DWORD);
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, pZA);
    ok(hr == S_OK, "got 0x%x for sizeof(ZONEATTRIBUTES) + sizeof(DWORD) (expected S_OK)\n", hr);

    pZA->cbSize = sizeof(ZONEATTRIBUTES) - sizeof(DWORD);
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, pZA);
    ok(hr == S_OK, "got 0x%x for sizeof(ZONEATTRIBUTES) - sizeof(DWORD) (expected S_OK)\n", hr);

    pZA->cbSize = 0;
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, pZA);
    ok(hr == S_OK, "got 0x%x for size 0 (expected S_OK)\n", hr);

    /* The key for the zone must be present, when calling SetZoneAttributes */
    myRegDeleteTreeA(HKEY_CURRENT_USER, regpath);
    /* E_FAIL is returned from IE6 here, which is reasonable.
       All newer IE return S_OK without saving the zone attributes to the registry.
       This is a Windows bug, but we have to accept that as standard */
    hr = IInternetZoneManager_SetZoneAttributes(zonemgr, URLZONE_CUSTOM, pZA);
    ok((hr == S_OK) || broken(hr == E_FAIL), "got 0x%x (expected S_OK)\n", hr);

    /* SetZoneAttributes did not create the directory */
    res = RegOpenKeyA(HKEY_CURRENT_USER, regpath, &hkey);
    ok((res == ERROR_FILE_NOT_FOUND) && (hkey == NULL),
        "got %u with %p (expected ERROR_FILE_NOT_FOUND with NULL)\n", res, hkey);

    if (hkey) RegCloseKey(hkey);

cleanup:
    /* delete zone settings in the registry */
    myRegDeleteTreeA(HKEY_CURRENT_USER, regpath);

    hr = IInternetZoneManager_Release(zonemgr);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);
}