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
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IInternetZoneManager_CreateZoneEnumerator (int /*<<< orphan*/ *,int*,int*,int) ; 
 scalar_t__ IInternetZoneManager_DestroyZoneEnumerator (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IInternetZoneManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_CreateZoneEnumerator(void)
{
    IInternetZoneManager *zonemgr = NULL;
    HRESULT hr;
    DWORD dwEnum;
    DWORD dwEnum2;
    DWORD dwCount;
    DWORD dwCount2;

    trace("testing zone enumerator...\n");

    hr = pCoInternetCreateZoneManager(NULL, &zonemgr, 0);
    ok(hr == S_OK, "CoInternetCreateZoneManager result: 0x%x\n", hr);
    if (FAILED(hr))
        return;

    dwEnum=0xdeadbeef;
    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum, NULL, 0);
    ok((hr == E_INVALIDARG) && (dwEnum == 0xdeadbeef),
        "got 0x%x with 0x%x (expected E_INVALIDARG with 0xdeadbeef)\n", hr, dwEnum);

    dwCount=0xdeadbeef;
    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, NULL, &dwCount, 0);
    ok((hr == E_INVALIDARG) && (dwCount == 0xdeadbeef),
        "got 0x%x and 0x%x (expected E_INVALIDARG and 0xdeadbeef)\n", hr, dwCount);

    dwEnum=0xdeadbeef;
    dwCount=0xdeadbeef;
    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum, &dwCount, 0xffffffff);
    ok((hr == E_INVALIDARG) && (dwEnum == 0xdeadbeef) && (dwCount == 0xdeadbeef),
        "got 0x%x with 0x%x and 0x%x (expected E_INVALIDARG with 0xdeadbeef and 0xdeadbeef)\n",
        hr, dwEnum, dwCount);

    dwEnum=0xdeadbeef;
    dwCount=0xdeadbeef;
    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum, &dwCount, 1);
    ok((hr == E_INVALIDARG) && (dwEnum == 0xdeadbeef) && (dwCount == 0xdeadbeef),
        "got 0x%x with 0x%x and 0x%x (expected E_INVALIDARG with 0xdeadbeef and 0xdeadbeef)\n",
        hr, dwEnum, dwCount);

    dwEnum=0xdeadbeef;
    dwCount=0xdeadbeef;
    /* Normal use */
    hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum, &dwCount, 0);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    if (SUCCEEDED(hr)) {
        dwEnum2=0xdeadbeef;
        dwCount2=0xdeadbeef;
        hr = IInternetZoneManager_CreateZoneEnumerator(zonemgr, &dwEnum2, &dwCount2, 0);
        ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);
        if (SUCCEEDED(hr)) {
            /* native urlmon has an incrementing counter for dwEnum */
            hr = IInternetZoneManager_DestroyZoneEnumerator(zonemgr, dwEnum2);
            ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);
        }

        hr = IInternetZoneManager_DestroyZoneEnumerator(zonemgr, dwEnum);
        ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

        /* Destroy the Enumerator twice is detected and handled in native urlmon */
        hr = IInternetZoneManager_DestroyZoneEnumerator(zonemgr, dwEnum);
        ok((hr == E_INVALIDARG), "got 0x%x (expected E_INVALIDARG)\n", hr);
    }

    /* ::Release succeed also, when a ::DestroyZoneEnumerator is missing */
    hr = IInternetZoneManager_Release(zonemgr);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);
}