#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwSize; int /*<<< orphan*/ * pReserved; void* bAllowWHQLChecks; void* dwDxDiagHeaderVersion; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IDxDiagProvider ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXDIAG_INIT_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DxDiagProvider ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* DXDIAG_DX9_SDK_VERSION ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 void* FALSE ; 
 scalar_t__ IDxDiagProvider_Initialize (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDxDiagProvider ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void test_Initialize(void)
{
    HRESULT hr;
    IDxDiagProvider *pddp;
    DXDIAG_INIT_PARAMS params;

    hr = CoCreateInstance(&CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IDxDiagProvider, (LPVOID*)&pddp);
    ok(hr == S_OK ||
       broken(hr == REGDB_E_CLASSNOTREG), /* Clean W2K3 */
       "Creating a IDxDiagProvider instance failed with %x\n", hr);
    if (FAILED(hr))
    {
        skip("Failed to create a IDxDiagProvider instance\n");
        return;
    }

    /* Test passing a NULL DXDIAG_INIT_PARAMS pointer. */
    hr = IDxDiagProvider_Initialize(pddp, NULL);
    ok(hr == E_POINTER,
       "Expected IDxDiagProvider::Initialize to return E_POINTER, got %x\n", hr);

    /* Test passing invalid dwSize values. */
    params.dwSize = 0;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == E_INVALIDARG,
       "Expected IDxDiagProvider::Initialize to return E_INVALIDARG, got %x\n", hr);

    params.dwSize = sizeof(params) + 1;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == E_INVALIDARG,
       "Expected IDxDiagProvider::Initialize to return E_INVALIDARG, got %x\n", hr);

    /* Test passing an unexpected dwDxDiagHeaderVersion value. */
    params.dwSize = sizeof(params);
    params.dwDxDiagHeaderVersion = 0;
    params.bAllowWHQLChecks = FALSE;
    params.pReserved = NULL;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == E_INVALIDARG,
       "Expected IDxDiagProvider::Initialize to return E_INVALIDARG, got %x\n", hr);

    /* Setting pReserved to a non-NULL value causes a crash on Windows. */
    if (0)
    {
        params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
        params.bAllowWHQLChecks = FALSE;
        params.pReserved = (VOID*)0xdeadbeef;
        hr = IDxDiagProvider_Initialize(pddp, &params);
        trace("IDxDiagProvider::Initialize returned %x\n", hr);
    }

    /* Test passing an appropriately initialized DXDIAG_INIT_PARAMS. */
    params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
    params.bAllowWHQLChecks = FALSE;
    params.pReserved = NULL;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == S_OK, "Expected IDxDiagProvider::Initialize to return S_OK, got %x\n", hr);

    /* Test initializing multiple times. */
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == S_OK, "Expected IDxDiagProvider::Initialize to return S_OK, got %x\n", hr);

    IDxDiagProvider_Release(pddp);
}