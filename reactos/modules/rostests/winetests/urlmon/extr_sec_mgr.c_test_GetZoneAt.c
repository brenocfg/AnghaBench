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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetZoneManager_CreateZoneEnumerator (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetZoneManager_DestroyZoneEnumerator (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IInternetZoneManager_GetZoneAt (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_GetZoneAt(void)
{
    IInternetZoneManager *zonemgr = NULL;
    HRESULT hr;
    DWORD dwEnum;
    DWORD dwCount;
    DWORD dwZone;
    DWORD i;

    trace("testing GetZoneAt...\n");

    hr = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hr == S_OK, "CoInternetCreateZoneManager result: 0x%x\n", hr);
    if (FAILED(hr))
        return;

    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum, &dwCount, 0);
    if (FAILED(hr))
        goto cleanup;

    if (0) {
        /* this crashes with native urlmon */
        IInternetZoneManager_GetZoneAt(zonemgr, dwEnum, 0, NULL);
    }

    dwZone = 0xdeadbeef;
    hr = IInternetZoneManager_GetZoneAt(zonemgr, 0xdeadbeef, 0, &dwZone);
    ok(hr == E_INVALIDARG,
        "got 0x%x with 0x%x (expected E_INVALIDARG)\n", hr, dwZone);

    for (i = 0; i < dwCount; i++)
    {
        dwZone = 0xdeadbeef;
        hr = IInternetZoneManager_GetZoneAt(zonemgr, dwEnum, i, &dwZone);
        ok(hr == S_OK, "#%d: got x%x with %d (expected S_OK)\n", i, hr, dwZone);
    }

    dwZone = 0xdeadbeef;
    /* MSDN (index .. must be .. less than or equal to) is wrong */
    hr = IInternetZoneManager_GetZoneAt(zonemgr, dwEnum, dwCount, &dwZone);
    ok(hr == E_INVALIDARG,
        "got 0x%x with 0x%x (expected E_INVALIDARG)\n", hr, dwZone);

    hr = IInternetZoneManager_DestroyZoneEnumerator(zonemgr, dwEnum);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

cleanup:
    hr = IInternetZoneManager_Release(zonemgr);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);
}